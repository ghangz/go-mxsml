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
	"strings"
)

type item struct {
	Name  string `json:"name"`
	Value string `json:"value"`
}

type catalog struct {
	PrimaryCount   int    `json:"primary_count"`
	ExtensionCount int    `json:"extension_count"`
	PrimaryFile    string `json:"primary_file"`
	ExtensionFile  string `json:"extension_file"`
	Primary        []item `json:"primary"`
	Extension      []item `json:"extension"`
}

func collectErrors(path string, prefix string) ([]item, error) {
	parsed, err := parser.ParseFile(token.NewFileSet(), path, nil, parser.SkipObjectResolution)
	if err != nil {
		return nil, err
	}
	var errors []item
	for _, declaration := range parsed.Decls {
		general, ok := declaration.(*ast.GenDecl)
		if !ok || general.Tok != token.CONST {
			continue
		}
		for _, specification := range general.Specs {
			valueSpec, ok := specification.(*ast.ValueSpec)
			if !ok {
				continue
			}
			for index, name := range valueSpec.Names {
				if !strings.HasPrefix(name.Name, prefix) || !strings.Contains(name.Name, "ERROR") {
					continue
				}
				value := ""
				if index < len(valueSpec.Values) {
					value = exprString(valueSpec.Values[index])
				}
				errors = append(errors, item{Name: name.Name, Value: value})
			}
		}
	}
	sort.Slice(errors, func(i, j int) bool { return errors[i].Name < errors[j].Name })
	return errors, nil
}

func exprString(expression ast.Expr) string {
	switch value := expression.(type) {
	case *ast.BasicLit:
		return value.Value
	case *ast.Ident:
		return value.Name
	default:
		return ""
	}
}

func run(repoRoot string) (catalog, error) {
	primaryFile := filepath.Join(repoRoot, "pkg", "mxsml", "const.go")
	extensionFile := filepath.Join(repoRoot, "pkg", "mxsmlextension", "const.go")
	primary, err := collectErrors(primaryFile, "MXSML_")
	if err != nil {
		return catalog{}, err
	}
	extension, err := collectErrors(extensionFile, "MXSMLEX_")
	if err != nil {
		return catalog{}, err
	}
	return catalog{
		PrimaryCount:   len(primary),
		ExtensionCount: len(extension),
		PrimaryFile:    filepath.ToSlash(primaryFile),
		ExtensionFile:  filepath.ToSlash(extensionFile),
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
