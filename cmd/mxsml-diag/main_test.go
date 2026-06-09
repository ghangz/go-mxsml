package main

import (
	"os"
	"path/filepath"
	"testing"
)

func TestBuildReportFindsExplicitLibrary(t *testing.T) {
	dir := t.TempDir()
	lib := filepath.Join(dir, "libmxsml.so")
	if err := os.WriteFile(lib, []byte{}, 0o644); err != nil {
		t.Fatal(err)
	}
	t.Setenv("MXSML_LIBRARY_PATH", lib)
	t.Setenv("LD_LIBRARY_PATH", "")

	report := buildReport()
	if !report.LibraryFound || report.SelectedLibrary != lib {
		t.Fatalf("unexpected report: %#v", report)
	}
}
