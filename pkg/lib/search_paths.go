package lib

const mxsmlLibName = "libmxsml.so"

// CandidateLibraryPaths returns the candidate absolute paths used to locate
// libmxsml.so after Load() has already tried the system loader search path.
func CandidateLibraryPaths() []string {
	return []string{
		"/opt/mxdriver/lib/" + mxsmlLibName,
		"/opt/maca/lib/" + mxsmlLibName,
		"/opt/mxn100/lib/" + mxsmlLibName,
	}
}
