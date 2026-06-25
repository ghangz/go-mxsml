package lib

import (
	"os"
	"path/filepath"
	"strings"
)

const mxsmlLibName = "libmxsml.so"

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
		for _, item := range strings.Split(value, string(os.PathListSeparator)) {
			item = strings.TrimSpace(item)
			if item == "" {
				continue
			}
			info, err := os.Stat(item)
			if err == nil && info.IsDir() {
				appendUnique(filepath.Join(item, mxsmlLibName))
			} else {
				appendUnique(item)
			}
		}
	}

	appendUnique("/opt/mxdriver/lib/" + mxsmlLibName)
	appendUnique("/opt/maca/lib/" + mxsmlLibName)
	appendUnique("/opt/mxn100/lib/" + mxsmlLibName)
	return paths
}
