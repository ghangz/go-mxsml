package main

import (
	"encoding/json"
	"flag"
	"fmt"
	"go/ast"
	"go/parser"
	"go/token"
	"os"
	"path/filepath"
	"sort"
	"strings"
)

type packageInfo struct {
	Path      string   `json:"path"`
	Function []string `json:"functions"`
}

type report struct {
	Headers  []string      `json:"headers"`
	Packages []packageInfo `json:"packages"`
}

func collectHeaders(root string) ([]string, error) {
	var headers []string
	err := filepath.WalkDir(filepath.Join(root, "gen"), func(path string, entry os.DirEntry, err error) error {
		if err != nil {
			return err
		}
		if !entry.IsDir() && strings.HasSuffix(entry.Name(), ".h") {
			rel, err := filepath.Rel(root, path)
			if err != nil {
				return err
			}
			headers = append(headers, filepath.ToSlash(rel))
		}
		return nil
	})
	sort.Strings(headers)
	return headers, err
}

func collectPackage(root, pkg string) (packageInfo, error) {
	fset := token.NewFileSet()
	out := packageInfo{Path: filepath.ToSlash(pkg)}
	fullPath := filepath.Join(root, pkg)
	entries, err := os.ReadDir(fullPath)
	if err != nil {
		return out, err
	}
	for _, entry := range entries {
		if entry.IsDir() || !strings.HasSuffix(entry.Name(), ".go") || strings.HasSuffix(entry.Name(), "_test.go") {
			continue
		}
		file, err := parser.ParseFile(fset, filepath.Join(fullPath, entry.Name()), nil, 0)
		if err != nil {
			return out, err
		}
		for _, decl := range file.Decls {
			fn, ok := decl.(*ast.FuncDecl)
			if ok && fn.Name.IsExported() {
				out.Function = append(out.Function, fn.Name.Name)
			}
		}
	}
	sort.Strings(out.Function)
	return out, nil
}

func buildReport(root string) (report, error) {
	headers, err := collectHeaders(root)
	if err != nil {
		return report{}, err
	}
	packages := make([]packageInfo, 0, 2)
	for _, pkg := range []string{"pkg/mxsml", "pkg/mxsmlextension"} {
		info, err := collectPackage(root, pkg)
		if err != nil {
			return report{}, err
		}
		packages = append(packages, info)
	}
	return report{Headers: headers, Packages: packages}, nil
}

func main() {
	root := flag.String("root", ".", "repository root")
	flag.Parse()

	out, err := buildReport(*root)
	if err != nil {
		fmt.Fprintln(os.Stderr, err)
		os.Exit(1)
	}
	encoded, err := json.MarshalIndent(out, "", "  ")
	if err != nil {
		fmt.Fprintln(os.Stderr, err)
		os.Exit(1)
	}
	fmt.Println(string(encoded))
}
