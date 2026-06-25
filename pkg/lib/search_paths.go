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

	if value := strings.TrimSpace(os.Getenv("LD_LIBRARY_PATH")); value != "" {
		for _, item := range strings.Split(value, ":") {
			item = strings.TrimSpace(item)
			if item == "" {
				continue
			}
			appendUnique(filepath.Join(item, mxsmlLibName))
		}
	}

	appendUnique("/opt/mxdriver/lib/" + mxsmlLibName)
	appendUnique("/opt/maca/lib/" + mxsmlLibName)
	appendUnique("/opt/mxn100/lib/" + mxsmlLibName)
	return paths
}
