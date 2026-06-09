package utils

import (
	"os"
	"path/filepath"
	"testing"
)

func TestResolveMxsmlLibraryFromExplicitFile(t *testing.T) {
	dir := t.TempDir()
	lib := filepath.Join(dir, "libmxsml.so")
	if err := os.WriteFile(lib, []byte{}, 0o644); err != nil {
		t.Fatal(err)
	}
	t.Setenv("MXSML_LIBRARY_PATH", lib)
	t.Setenv("LD_LIBRARY_PATH", "")

	got, ok := ResolveMxsmlLibrary()
	if !ok || got != lib {
		t.Fatalf("ResolveMxsmlLibrary() = %q, %v; want %q, true", got, ok, lib)
	}
}

func TestMxsmlLibraryCandidatesExpandsDirectory(t *testing.T) {
	dir := t.TempDir()
	lib := filepath.Join(dir, "libmxsml.so")
	if err := os.WriteFile(lib, []byte{}, 0o644); err != nil {
		t.Fatal(err)
	}
	t.Setenv("MXSML_LIBRARY_PATH", "")
	t.Setenv("LD_LIBRARY_PATH", dir)

	candidates := MxsmlLibraryCandidates()
	if len(candidates) == 0 || candidates[0].Path != lib || !candidates[0].Exists {
		t.Fatalf("unexpected first candidate: %#v", candidates)
	}
}
