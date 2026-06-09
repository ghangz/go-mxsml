package main

import (
	"encoding/json"
	"fmt"
	"os"
	"path/filepath"
	"runtime"
	"strings"
)

type candidate struct {
	Path   string `json:"path"`
	Source string `json:"source"`
	Exists bool   `json:"exists"`
}

type report struct {
	GOOS            string      `json:"goos"`
	GOARCH          string      `json:"goarch"`
	LibraryFound    bool        `json:"library_found"`
	SelectedLibrary string      `json:"selected_library,omitempty"`
	Candidates      []candidate `json:"candidates"`
}

func addCandidate(out *[]candidate, seen map[string]struct{}, path, source string) {
	path = strings.TrimSpace(path)
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
	*out = append(*out, candidate{Path: path, Source: source, Exists: err == nil})
}

func buildReport() report {
	seen := map[string]struct{}{}
	var candidates []candidate
	for _, path := range filepath.SplitList(os.Getenv("MXSML_LIBRARY_PATH")) {
		addCandidate(&candidates, seen, path, "MXSML_LIBRARY_PATH")
	}
	for _, path := range filepath.SplitList(os.Getenv("LD_LIBRARY_PATH")) {
		addCandidate(&candidates, seen, path, "LD_LIBRARY_PATH")
	}
	for _, path := range []string{
		"/opt/mxdriver/lib/libmxsml.so",
		"/opt/maca/lib/libmxsml.so",
		"/opt/mxn100/lib/libmxsml.so",
	} {
		addCandidate(&candidates, seen, path, "default")
	}

	out := report{GOOS: runtime.GOOS, GOARCH: runtime.GOARCH, Candidates: candidates}
	for _, item := range candidates {
		if item.Exists {
			out.LibraryFound = true
			out.SelectedLibrary = item.Path
			break
		}
	}
	return out
}

func main() {
	out := buildReport()
	encoded, err := json.MarshalIndent(out, "", "  ")
	if err != nil {
		fmt.Fprintln(os.Stderr, err)
		os.Exit(1)
	}
	fmt.Println(string(encoded))
	if !out.LibraryFound {
		os.Exit(2)
	}
}
