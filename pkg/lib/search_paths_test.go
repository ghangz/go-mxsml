package lib

import (
	"path/filepath"
	"testing"
)

func TestCandidateLibraryPathsUsesLdLibraryPath(t *testing.T) {
	t.Setenv("LD_LIBRARY_PATH", "/custom/one:/custom/two")

	paths := candidateLibraryPaths()
	if len(paths) < 2 {
		t.Fatalf("expected LD_LIBRARY_PATH entries in candidate list, got %v", paths)
	}
	if paths[0] != filepath.Join("/custom/one", mxsmlLibName) {
		t.Fatalf("unexpected first path: %v", paths)
	}
	if paths[1] != filepath.Join("/custom/two", mxsmlLibName) {
		t.Fatalf("unexpected second path: %v", paths)
	}
}

func TestCandidateLibraryPathsDeduplicatesLdEntries(t *testing.T) {
	t.Setenv("LD_LIBRARY_PATH", "/custom/one:/custom/one")

	paths := candidateLibraryPaths()
	count := 0
	for _, path := range paths {
		if path == filepath.Join("/custom/one", mxsmlLibName) {
			count++
		}
	}
	if count != 1 {
		t.Fatalf("expected deduplicated LD_LIBRARY_PATH entry, got %v", paths)
	}
}
