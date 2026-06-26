package lib

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

	appendUnique("/opt/mxdriver/lib/" + mxsmlLibName)
	appendUnique("/opt/maca/lib/" + mxsmlLibName)
	appendUnique("/opt/mxn100/lib/" + mxsmlLibName)
	return paths
}
