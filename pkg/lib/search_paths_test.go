package lib

import "testing"

func TestCandidateLibraryPathsOrder(t *testing.T) {
	paths := CandidateLibraryPaths()
	want := []string{
		"/opt/mxdriver/lib/libmxsml.so",
		"/opt/maca/lib/libmxsml.so",
		"/opt/mxn100/lib/libmxsml.so",
	}
	if len(paths) != len(want) {
		t.Fatalf("expected %d paths, got %d: %v", len(want), len(paths), paths)
	}
	for i := range want {
		if paths[i] != want[i] {
			t.Fatalf("expected path %d to be %s, got %s", i, want[i], paths[i])
		}
	}
}
