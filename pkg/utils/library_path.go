// "Copyright (c) 2026 MetaX Integrated Circuits (Shanghai) Co., Ltd. All rights reserved."
package utils

import (
	"os"
	"path/filepath"
	"strings"
)

var defaultMxsmlLibraryPaths = []string{
	"/opt/mxdriver/lib/libmxsml.so",
	"/opt/maca/lib/libmxsml.so",
	"/opt/mxn100/lib/libmxsml.so",
}

// MxsmlLibraryCandidate describes one location checked for libmxsml.so.
type MxsmlLibraryCandidate struct {
	Path   string
	Source string
	Exists bool
}

// ResolveMxsmlLibrary returns the first visible libmxsml.so candidate.
func ResolveMxsmlLibrary() (string, bool) {
	for _, candidate := range MxsmlLibraryCandidates() {
		if candidate.Exists {
			return candidate.Path, true
		}
	}
	return "", false
}

// MxsmlLibraryCandidates lists libmxsml.so lookup candidates in diagnostic order.
func MxsmlLibraryCandidates() []MxsmlLibraryCandidate {
	seen := map[string]struct{}{}
	var out []MxsmlLibraryCandidate
	add := func(path, source string) {
		if path == "" {
			return
		}
		if !strings.HasSuffix(path, ".so") {
			path = filepath.Join(path, "libmxsml.so")
		}
		if _, ok := seen[path]; ok {
			return
		}
		seen[path] = struct{}{}
		_, err := os.Stat(path)
		out = append(out, MxsmlLibraryCandidate{Path: path, Source: source, Exists: err == nil})
	}

	for _, path := range filepath.SplitList(os.Getenv("MXSML_LIBRARY_PATH")) {
		add(strings.TrimSpace(path), "MXSML_LIBRARY_PATH")
	}
	for _, path := range filepath.SplitList(os.Getenv("LD_LIBRARY_PATH")) {
		add(strings.TrimSpace(path), "LD_LIBRARY_PATH")
	}
	for _, path := range defaultMxsmlLibraryPaths {
		add(path, "default")
	}
	return out
}
