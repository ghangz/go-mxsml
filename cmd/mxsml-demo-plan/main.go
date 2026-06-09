package main

import (
	"encoding/json"
	"fmt"
)

type step struct {
	Name    string `json:"name"`
	Command string `json:"command"`
}

func main() {
	steps := []step{
		{Name: "build demos", Command: "make demo"},
		{Name: "run mxsml demo", Command: "./demo/bin/mxsmlDemo"},
		{Name: "run mxsml extension demo", Command: "./demo/bin/mxsmlExtDemo"},
	}
	encoded, _ := json.MarshalIndent(map[string]any{"step_count": len(steps), "steps": steps}, "", "  ")
	fmt.Println(string(encoded))
}
