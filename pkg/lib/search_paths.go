package lib

const mxsmlLibName = "libmxsml.so"

func CandidateLibraryPaths() []string {
	return []string{
		"/opt/mxdriver/lib/" + mxsmlLibName,
		"/opt/maca/lib/" + mxsmlLibName,
		"/opt/mxn100/lib/" + mxsmlLibName,
	}
}
