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

type aliasItem struct {
	Name   string `json:"name"`
	Target string `json:"target"`
}

type audit struct {
	PrimaryCount   int         `json:"primary_count"`
	ExtensionCount int         `json:"extension_count"`
	Primary        []aliasItem `json:"primary"`
	Extension      []aliasItem `json:"extension"`
}

func collectAliases(path string) ([]aliasItem, error) {
	parsed, err := parser.ParseFile(token.NewFileSet(), path, nil, parser.SkipObjectResolution)
	if err != nil {
		return nil, err
	}
	var aliases []aliasItem
	for _, declaration := range parsed.Decls {
		general, ok := declaration.(*ast.GenDecl)
		if !ok || general.Tok != token.VAR {
			continue
		}
		for _, specification := range general.Specs {
			valueSpec, ok := specification.(*ast.ValueSpec)
			if !ok {
				continue
			}
			for index, name := range valueSpec.Names {
				target := ""
				if index < len(valueSpec.Values) {
					target = exprString(valueSpec.Values[index])
				}
				aliases = append(aliases, aliasItem{Name: name.Name, Target: target})
			}
		}
	}
	sort.Slice(aliases, func(i, j int) bool { return aliases[i].Name < aliases[j].Name })
	return aliases, nil
}

func exprString(expression ast.Expr) string {
	switch value := expression.(type) {
	case *ast.SelectorExpr:
		return exprString(value.X) + "." + value.Sel.Name
	case *ast.Ident:
		return value.Name
	default:
		return ""
	}
}

func run(repoRoot string) (audit, error) {
	primary, err := collectAliases(filepath.Join(repoRoot, "pkg", "mxsml", "api.go"))
	if err != nil {
		return audit{}, err
	}
	extension, err := collectAliases(filepath.Join(repoRoot, "pkg", "mxsmlextension", "api.go"))
	if err != nil {
		return audit{}, err
	}
	return audit{
		PrimaryCount:   len(primary),
		ExtensionCount: len(extension),
		Primary:        primary,
		Extension:      extension,
	}, nil
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
