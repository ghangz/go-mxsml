package lib

import "testing"

func TestCandidateLibraryPathsIgnoreLdLibraryPath(t *testing.T) {
	t.Setenv("LD_LIBRARY_PATH", "/custom/one:/custom/two")

	paths := candidateLibraryPaths()
	if len(paths) != 3 {
		t.Fatalf("expected only default fallback paths, got %v", paths)
	}
}
