package main

import (
	"crypto/sha256"
	"encoding/hex"
	"encoding/json"
	"flag"
	"fmt"
	"os"
	"path/filepath"
	"sort"
	"strings"
)

type item struct {
	Path   string `json:"path"`
	SHA256 string `json:"sha256"`
}

func collect(root string) ([]item, error) {
	var out []item
	err := filepath.WalkDir(filepath.Join(root, "gen"), func(path string, entry os.DirEntry, err error) error {
		if err != nil || entry.IsDir() || !strings.HasSuffix(entry.Name(), ".h") {
			return err
		}
		data, err := os.ReadFile(path)
		if err != nil {
			return err
		}
		sum := sha256.Sum256(data)
		rel, _ := filepath.Rel(root, path)
		out = append(out, item{Path: filepath.ToSlash(rel), SHA256: hex.EncodeToString(sum[:])})
		return nil
	})
	sort.Slice(out, func(i, j int) bool { return out[i].Path < out[j].Path })
	return out, err
}

func main() {
	root := flag.String("root", ".", "repository root")
	flag.Parse()
	items, err := collect(*root)
	if err != nil {
		fmt.Fprintln(os.Stderr, err)
		os.Exit(1)
	}
	encoded, _ := json.MarshalIndent(map[string]any{"header_count": len(items), "headers": items}, "", "  ")
	fmt.Println(string(encoded))
}
