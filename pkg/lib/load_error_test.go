package lib

import (
	"errors"
	"strings"
	"testing"
)

func TestLoadErrorIncludesPathsAndCause(t *testing.T) {
	err := newLoadError([]string{"/opt/maca/lib/libmxsml.so", "/opt/mxdriver/lib/libmxsml.so"}, errors.New("dlopen failed"))
	message := err.Error()
	if !strings.Contains(message, "/opt/maca/lib/libmxsml.so") {
		t.Fatalf("expected path in error message, got %s", message)
	}
	if !strings.Contains(message, "dlopen failed") {
		t.Fatalf("expected cause in error message, got %s", message)
	}
}

func TestLoadErrorCopiesAttemptedPaths(t *testing.T) {
	paths := []string{"/opt/maca/lib/libmxsml.so"}
	err := newLoadError(paths, nil).(*LoadError)
	paths[0] = "/mutated"
	if err.AttemptedPaths[0] != "/opt/maca/lib/libmxsml.so" {
		t.Fatalf("expected attempted paths to be copied, got %v", err.AttemptedPaths)
	}
}

func TestLoadErrorUnwrap(t *testing.T) {
	cause := errors.New("dlopen failed")
	err := newLoadError(nil, cause)
	if !errors.Is(err, cause) {
		t.Fatalf("expected wrapped error to be unwrappable, got %v", err)
	}
}
