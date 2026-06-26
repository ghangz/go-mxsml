package lib

import (
	"os"
	"path/filepath"
	"strings"
)

const mxsmlLibName = "libmxsml.so"

func hasExplicitLibraryPathConfig() bool {
	return strings.TrimSpace(os.Getenv("MXSML_LIBRARY_PATH")) != "" ||
		strings.TrimSpace(os.Getenv("MACA_HOME")) != ""
}

func candidateLibraryPaths() []string {
	paths := []string{}
	appendUnique := func(path string) {
		if path == "" {
			return
		}
		for _, existing := range paths {
			if existing == path {
				return
			}
		}
		paths = append(paths, path)
	}

	if value := strings.TrimSpace(os.Getenv("MXSML_LIBRARY_PATH")); value != "" {
		info, err := os.Stat(value)
		if err == nil && info.IsDir() {
			appendUnique(filepath.Join(value, mxsmlLibName))
		} else {
			appendUnique(value)
		}
	}

	if value := strings.TrimSpace(os.Getenv("MACA_HOME")); value != "" {
		appendUnique(filepath.Join(value, "lib", mxsmlLibName))
	}

	if hasExplicitLibraryPathConfig() {
		return paths
	}

	appendUnique("/opt/mxdriver/lib/" + mxsmlLibName)
	appendUnique("/opt/maca/lib/" + mxsmlLibName)
	appendUnique("/opt/mxn100/lib/" + mxsmlLibName)
	return paths
}
