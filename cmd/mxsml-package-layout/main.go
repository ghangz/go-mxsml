package main

import (
	"encoding/json"
	"flag"
	"os"
	"path/filepath"
	"sort"
)

type layout struct {
	CommandCount int      `json:"command_count"`
	DemoCount    int      `json:"demo_count"`
	PackageCount int      `json:"package_count"`
	GenCount     int      `json:"gen_count"`
	Commands     []string `json:"commands"`
	Demos        []string `json:"demos"`
	Packages     []string `json:"packages"`
	Generated    []string `json:"generated"`
}

func listDirectories(root string) ([]string, error) {
	entries, err := os.ReadDir(root)
	if err != nil {
		return nil, err
	}
	var results []string
	for _, entry := range entries {
		if entry.IsDir() {
			results = append(results, entry.Name())
		}
	}
	sort.Strings(results)
	return results, nil
}

func run(repoRoot string) (layout, error) {
	commands, err := listDirectories(filepath.Join(repoRoot, "cmd"))
	if err != nil {
		return layout{}, err
	}
	demos, err := listDirectories(filepath.Join(repoRoot, "demo"))
	if err != nil {
		return layout{}, err
	}
	packages, err := listDirectories(filepath.Join(repoRoot, "pkg"))
	if err != nil {
		return layout{}, err
	}
	generated, err := listDirectories(filepath.Join(repoRoot, "gen"))
	if err != nil {
		return layout{}, err
	}
	return layout{
		CommandCount: len(commands),
		DemoCount:    len(demos),
		PackageCount: len(packages),
		GenCount:     len(generated),
		Commands:     commands,
		Demos:        demos,
		Packages:     packages,
		Generated:    generated,
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
