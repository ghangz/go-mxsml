package main

import (
	"os"
	"path/filepath"
	"testing"
)

func writeFixture(t *testing.T, path string, body string) {
	t.Helper()
	if err := os.MkdirAll(filepath.Dir(path), 0o755); err != nil {
		t.Fatal(err)
	}
	if err := os.WriteFile(path, []byte(body), 0o644); err != nil {
		t.Fatal(err)
	}
}

func TestCollectEnumGroups(t *testing.T) {
	root := t.TempDir()
	writeFixture(t, filepath.Join(root, "pkg", "mxsml", "const.go"), `package mxsml
type State int32
const (
	StateA State = iota
	StateB
)
`)
	writeFixture(t, filepath.Join(root, "pkg", "mxsmlextension", "const.go"), `package mxsmlextension
type Mode int32
const (
	ModeA Mode = iota
)
`)

	report, err := run(root)
	if err != nil {
		t.Fatal(err)
	}
	if report.Primary[0].ValueCount != 2 {
		t.Fatalf("unexpected primary values: %d", report.Primary[0].ValueCount)
	}
	if report.Extension[0].TypeName != "Mode" {
		t.Fatalf("unexpected extension type: %s", report.Extension[0].TypeName)
	}
}
