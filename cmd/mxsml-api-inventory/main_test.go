package main

import "testing"

func TestBuildReportFindsHeadersAndPackages(t *testing.T) {
	report, err := buildReport("../..")
	if err != nil {
		t.Fatal(err)
	}
	if len(report.Headers) == 0 {
		t.Fatalf("expected generated headers")
	}
	if len(report.Packages) != 2 {
		t.Fatalf("expected two packages, got %d", len(report.Packages))
	}
	for _, pkg := range report.Packages {
		if len(pkg.Function) == 0 {
			t.Fatalf("expected exported functions in %s", pkg.Path)
		}
	}
}
