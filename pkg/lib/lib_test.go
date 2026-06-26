package lib

import (
	"os"
	"path/filepath"
	"testing"
)

func TestCandidateLibraryPathsUsesEnvFile(t *testing.T) {
	t.Setenv("MXSML_LIBRARY_PATH", "/custom/libmxsml.so")
	t.Setenv("MACA_HOME", "")

	paths := candidateLibraryPaths()
	if len(paths) != 1 || paths[0] != "/custom/libmxsml.so" {
		t.Fatalf("expected env file path first, got %v", paths)
	}
}

func TestCandidateLibraryPathsUsesEnvDirectory(t *testing.T) {
	dir := t.TempDir()
	t.Setenv("MXSML_LIBRARY_PATH", dir)
	t.Setenv("MACA_HOME", "")

	paths := candidateLibraryPaths()
	want := filepath.Join(dir, mxsmlLibName)
	if len(paths) != 1 || paths[0] != want {
		t.Fatalf("expected env directory to resolve to %s, got %v", want, paths)
	}
}

func TestCandidateLibraryPathsUsesMacaHome(t *testing.T) {
	t.Setenv("MXSML_LIBRARY_PATH", "")
	t.Setenv("MACA_HOME", "/opt/custom-maca")

	paths := candidateLibraryPaths()
	want := filepath.Join("/opt/custom-maca", "lib", mxsmlLibName)
	if len(paths) != 1 || paths[0] != want {
		t.Fatalf("expected only explicit MACA_HOME path %s, got %v", want, paths)
	}
}

func TestCandidateLibraryPathsSkipsDuplicates(t *testing.T) {
	t.Setenv("MXSML_LIBRARY_PATH", filepath.Join("/opt/maca/lib", mxsmlLibName))
	t.Setenv("MACA_HOME", "/opt/maca")

	paths := candidateLibraryPaths()
	seen := map[string]struct{}{}
	for _, path := range paths {
		if _, ok := seen[path]; ok {
			t.Fatalf("found duplicate path %s in %v", path, paths)
		}
		seen[path] = struct{}{}
	}
}

func TestCandidateLibraryPathsHandlesMissingEnvDirAsFile(t *testing.T) {
	missing := filepath.Join(os.TempDir(), "missing-libmxsml.so")
	t.Setenv("MXSML_LIBRARY_PATH", missing)
	t.Setenv("MACA_HOME", "")

	paths := candidateLibraryPaths()
	if len(paths) == 0 || paths[0] != missing {
		t.Fatalf("expected missing env path to be preserved, got %v", paths)
	}
}

func TestCandidateLibraryPathsFallsBackToDefaultsWithoutExplicitConfig(t *testing.T) {
	t.Setenv("MXSML_LIBRARY_PATH", "")
	t.Setenv("MACA_HOME", "")

	paths := candidateLibraryPaths()
	if len(paths) != 3 {
		t.Fatalf("expected default paths, got %v", paths)
	}
}
