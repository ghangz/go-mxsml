package main

import (
	"crypto/sha256"
	"encoding/hex"
	"encoding/json"
	"flag"
	"io"
	"os"
	"path/filepath"
	"sort"
	"strings"
)

type fileItem struct {
	Path   string `json:"path"`
	Size   int64  `json:"size"`
	SHA256 string `json:"sha256"`
}

type manifest struct {
	FileCount int        `json:"file_count"`
	Files     []fileItem `json:"files"`
}

func include(path string) bool {
	slash := filepath.ToSlash(path)
	return strings.HasPrefix(slash, "gen/") || strings.HasSuffix(slash, "types_gen.go") || strings.HasSuffix(slash, "cgo_helpers_static.go")
}

func digest(path string) (string, int64, error) {
	file, err := os.Open(path)
	if err != nil {
		return "", 0, err
	}
	defer file.Close()

	hash := sha256.New()
	size, err := io.Copy(hash, file)
	if err != nil {
		return "", 0, err
	}
	return hex.EncodeToString(hash.Sum(nil)), size, nil
}

func run(repoRoot string) (manifest, error) {
	var files []fileItem
	err := filepath.WalkDir(repoRoot, func(path string, entry os.DirEntry, err error) error {
		if err != nil || entry.IsDir() {
			return err
		}
		relative, err := filepath.Rel(repoRoot, path)
		if err != nil || !include(relative) {
			return err
		}
		sum, size, err := digest(path)
		if err != nil {
			return err
		}
		files = append(files, fileItem{Path: filepath.ToSlash(relative), Size: size, SHA256: sum})
		return nil
	})
	if err != nil {
		return manifest{}, err
	}
	sort.Slice(files, func(i, j int) bool { return files[i].Path < files[j].Path })
	return manifest{FileCount: len(files), Files: files}, nil
}

func main() {
	repoRoot := flag.String("repo-root", ".", "Repository root")
	flag.Parse()

	report, err := run(*repoRoot)
	if err != nil {
		panic(err)
	}
	encoder := json.NewEncoder(os.Stdout)
	encoder.SetIndent("", "  ")
	_ = encoder.Encode(report)
}
