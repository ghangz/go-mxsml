package lib

import (
	"fmt"
	"strings"
)

type LoadError struct {
	AttemptedPaths []string
	Cause          error
}

func (e *LoadError) Error() string {
	parts := []string{"failed to load libmxsml.so"}
	if len(e.AttemptedPaths) > 0 {
		parts = append(parts, fmt.Sprintf("attempted paths: %s", strings.Join(e.AttemptedPaths, ", ")))
	}
	if e.Cause != nil {
		parts = append(parts, fmt.Sprintf("cause: %v", e.Cause))
	}
	return strings.Join(parts, "; ")
}

func (e *LoadError) Unwrap() error {
	return e.Cause
}

func newLoadError(paths []string, cause error) error {
	return &LoadError{
		AttemptedPaths: append([]string(nil), paths...),
		Cause:          cause,
	}
}
