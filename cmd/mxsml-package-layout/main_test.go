package main

import (
	"os"
	"path/filepath"
	"testing"
)

func mkdir(t *testing.T, path string) {
	t.Helper()
	if err := os.MkdirAll(path, 0o755); err != nil {
		t.Fatal(err)
	}
}

func TestRunListsTopLevelGroups(t *testing.T) {
	root := t.TempDir()
	mkdir(t, filepath.Join(root, "cmd", "mxsml-diag"))
	mkdir(t, filepath.Join(root, "demo", "mxsml"))
	mkdir(t, filepath.Join(root, "pkg", "mxsml"))
	mkdir(t, filepath.Join(root, "gen", "mxsml"))

	report, err := run(root)
	if err != nil {
		t.Fatal(err)
	}
	if report.CommandCount != 1 || report.DemoCount != 1 || report.PackageCount != 1 || report.GenCount != 1 {
		t.Fatalf("unexpected layout counts: %+v", report)
	}
}
