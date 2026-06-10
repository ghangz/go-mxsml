package main

import (
	"encoding/json"
	"flag"
	"go/ast"
	"go/parser"
	"go/token"
	"os"
	"path/filepath"
	"sort"
)

type enumGroup struct {
	TypeName   string   `json:"type_name"`
	ValueCount int      `json:"value_count"`
	Values     []string `json:"values"`
}

type inventory struct {
	Primary   []enumGroup `json:"primary"`
	Extension []enumGroup `json:"extension"`
}

func collectEnumGroups(path string) ([]enumGroup, error) {
	parsed, err := parser.ParseFile(token.NewFileSet(), path, nil, parser.SkipObjectResolution)
	if err != nil {
		return nil, err
	}
	typeNames := map[string]bool{}
	for _, declaration := range parsed.Decls {
		general, ok := declaration.(*ast.GenDecl)
		if !ok || general.Tok != token.TYPE {
			continue
		}
		for _, specification := range general.Specs {
			typeSpec, ok := specification.(*ast.TypeSpec)
			if ok {
				typeNames[typeSpec.Name.Name] = true
			}
		}
	}

	grouped := map[string][]string{}
	for _, declaration := range parsed.Decls {
		general, ok := declaration.(*ast.GenDecl)
		if !ok || general.Tok != token.CONST {
			continue
		}
		currentType := ""
		for _, specification := range general.Specs {
			valueSpec, ok := specification.(*ast.ValueSpec)
			if !ok {
				continue
			}
			if valueSpec.Type != nil {
				identifier, ok := valueSpec.Type.(*ast.Ident)
				if !ok || !typeNames[identifier.Name] {
					currentType = ""
					continue
				}
				currentType = identifier.Name
			}
			if currentType == "" {
				continue
			}
			for _, name := range valueSpec.Names {
				grouped[currentType] = append(grouped[currentType], name.Name)
			}
		}
	}

	groups := make([]enumGroup, 0, len(grouped))
	for typeName, values := range grouped {
		groups = append(groups, enumGroup{TypeName: typeName, ValueCount: len(values), Values: values})
	}
	sort.Slice(groups, func(i, j int) bool { return groups[i].TypeName < groups[j].TypeName })
	return groups, nil
}

func run(repoRoot string) (inventory, error) {
	primary, err := collectEnumGroups(filepath.Join(repoRoot, "pkg", "mxsml", "const.go"))
	if err != nil {
		return inventory{}, err
	}
	extension, err := collectEnumGroups(filepath.Join(repoRoot, "pkg", "mxsmlextension", "const.go"))
	if err != nil {
		return inventory{}, err
	}
	return inventory{Primary: primary, Extension: extension}, nil
}

func main() {
	repoRoot := flag.String("repo-root", ".", "Repository root")
	flag.Parse()

	report, err := run(*repoRoot)
	if err != nil {
		panic(err)
	}
	encoder := json.NewEncoder(os.Stdout)
	encoder.SetIndent("", "  ")
	_ = encoder.Encode(report)
}
