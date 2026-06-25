package lib

import (
	"os"
	"path/filepath"
	"testing"
)

func TestCandidateLibraryPathsExpandsPathList(t *testing.T) {
	dir1 := t.TempDir()
	dir2 := t.TempDir()
	value := dir1 + string(os.PathListSeparator) + filepath.Join(dir2, mxsmlLibName)
	t.Setenv("MXSML_LIBRARY_PATH", value)

	paths := candidateLibraryPaths()
	if len(paths) < 2 {
		t.Fatalf("expected at least 2 paths, got %v", paths)
	}
	if paths[0] != filepath.Join(dir1, mxsmlLibName) {
		t.Fatalf("expected first path to resolve directory entry, got %v", paths)
	}
	if paths[1] != filepath.Join(dir2, mxsmlLibName) {
		t.Fatalf("expected second path to preserve file entry, got %v", paths)
	}
}

func TestCandidateLibraryPathsDeduplicatesEntries(t *testing.T) {
	dir := t.TempDir()
	value := dir + string(os.PathListSeparator) + dir
	t.Setenv("MXSML_LIBRARY_PATH", value)

	paths := candidateLibraryPaths()
	seen := map[string]struct{}{}
	for _, path := range paths {
		if _, ok := seen[path]; ok {
			t.Fatalf("found duplicate path %s in %v", path, paths)
		}
		seen[path] = struct{}{}
	}
}
