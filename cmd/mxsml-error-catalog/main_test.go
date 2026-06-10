package main

import (
	"os"
	"path/filepath"
	"testing"
)

func writeFile(t *testing.T, path string, body string) {
	t.Helper()
	if err := os.MkdirAll(filepath.Dir(path), 0o755); err != nil {
		t.Fatal(err)
	}
	if err := os.WriteFile(path, []byte(body), 0o644); err != nil {
		t.Fatal(err)
	}
}

func TestCollectErrors(t *testing.T) {
	root := t.TempDir()
	writeFile(t, filepath.Join(root, "pkg", "mxsml", "const.go"), `package mxsml
const (
	MXSML_SUCCESS = 0
	MXSML_ERROR_FAILURE = 1
	MXSML_ERROR_BUSY = 2
)`)
	writeFile(t, filepath.Join(root, "pkg", "mxsmlextension", "const.go"), `package mxsmlextension
const (
	MXSMLEX_SUCCESS = 0
	MXSMLEX_ERROR_TIMEOUT = 10
)`)

	report, err := run(root)
	if err != nil {
		t.Fatal(err)
	}
	if report.PrimaryCount != 2 {
		t.Fatalf("unexpected primary count: %d", report.PrimaryCount)
	}
	if report.ExtensionCount != 1 {
		t.Fatalf("unexpected extension count: %d", report.ExtensionCount)
	}
}
