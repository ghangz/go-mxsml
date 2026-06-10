package main

import (
	"os"
	"path/filepath"
	"testing"
)

func writeAliasFixture(t *testing.T, path string, body string) {
	t.Helper()
	if err := os.MkdirAll(filepath.Dir(path), 0o755); err != nil {
		t.Fatal(err)
	}
	if err := os.WriteFile(path, []byte(body), 0o644); err != nil {
		t.Fatal(err)
	}
}

func TestRunCollectsAliasTargets(t *testing.T) {
	root := t.TempDir()
	writeAliasFixture(t, filepath.Join(root, "pkg", "mxsml", "api.go"), `package mxsml
var (
	Init = wrapper.Init
)
`)
	writeAliasFixture(t, filepath.Join(root, "pkg", "mxsmlextension", "api.go"), `package mxsmlextension
var (
	DeviceGetCount = extensionWrapper.DeviceGetCount
)
`)

	report, err := run(root)
	if err != nil {
		t.Fatal(err)
	}
	if report.Primary[0].Target != "wrapper.Init" {
		t.Fatalf("unexpected target: %s", report.Primary[0].Target)
	}
	if report.ExtensionCount != 1 {
		t.Fatalf("unexpected extension count: %d", report.ExtensionCount)
	}
}
