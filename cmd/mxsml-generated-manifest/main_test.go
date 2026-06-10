package main

import (
	"os"
	"path/filepath"
	"testing"
)

func writeGenerated(t *testing.T, path string) {
	t.Helper()
	if err := os.MkdirAll(filepath.Dir(path), 0o755); err != nil {
		t.Fatal(err)
	}
	if err := os.WriteFile(path, []byte("package demo\n"), 0o644); err != nil {
		t.Fatal(err)
	}
}

func TestRunIncludesGeneratedFiles(t *testing.T) {
	root := t.TempDir()
	writeGenerated(t, filepath.Join(root, "gen", "mxsml", "MxSml.h"))
	writeGenerated(t, filepath.Join(root, "pkg", "mxsml", "types_gen.go"))
	writeGenerated(t, filepath.Join(root, "pkg", "mxsml", "api.go"))

	report, err := run(root)
	if err != nil {
		t.Fatal(err)
	}
	if report.FileCount != 2 {
		t.Fatalf("unexpected file count: %d", report.FileCount)
	}
}
