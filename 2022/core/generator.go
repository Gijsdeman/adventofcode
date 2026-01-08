package core

import (
	"fmt"
	"os"
	"path/filepath"
)

// GenerateDay creates a new day folder with template files
func GenerateDay(day int, workspaceRoot string, sessionCookie string, year int) error {
	dayFolder := filepath.Join(workspaceRoot, fmt.Sprintf("day%02d", day))
	dayFile := filepath.Join(dayFolder, fmt.Sprintf("day%02d.go", day))
	inputFile := filepath.Join(dayFolder, "input")
	exampleFile := filepath.Join(dayFolder, "example")

	if _, err := os.Stat(dayFile); err == nil {
		fmt.Printf("Day %02d already exists at %s, skipping generation\n", day, dayFolder)
		return nil
	}

	if err := os.MkdirAll(dayFolder, 0755); err != nil {
		return fmt.Errorf("failed to create day folder: %w", err)
	}

	template := GenerateDayTemplate(day)
	if err := os.WriteFile(dayFile, []byte(template), 0644); err != nil {
		return fmt.Errorf("failed to write day file: %w", err)
	}

	if _, err := os.Stat(exampleFile); os.IsNotExist(err) {
		if err := os.WriteFile(exampleFile, []byte(""), 0644); err != nil {
			return fmt.Errorf("failed to write example file: %w", err)
		}
	}

	if _, err := os.Stat(inputFile); os.IsNotExist(err) {
		fetcher := NewInputFetcher(sessionCookie, year)
		if err := fetcher.FetchAndSaveInput(day, inputFile); err != nil {
			return fmt.Errorf("failed to fetch input: %w", err)
		}
	}

	fmt.Printf("Day %02d generated successfully at %s\n", day, dayFolder)
	return nil
}

// GenerateDayTemplate creates the template code for a new day
func GenerateDayTemplate(day int) string {
	return fmt.Sprintf(`package main

import (
	"adventofcode/2022/core"
	_ "embed"
	"fmt"
	"strings"
)

//go:embed input
var input string

//go:embed example
var example string

type Day%02d struct{}

var _ core.DayBase = Day%02d{}

func (d Day%02d) Part1(input string) string {
	defer core.Timer("Part 1")()

	lines := core.GetLines(strings.TrimSpace(input), true)
	_ = lines

	return fmt.Sprintf("%%d", 0)
}

func (d Day%02d) Part2(input string) string {
	defer core.Timer("Part 2")()

	lines := core.GetLines(strings.TrimSpace(input), true)
	_ = lines
	
	return fmt.Sprintf("%%d", 0)
}

func main() {
	core.RunDays(Day%02d{}, input, example)
}
`, day, day, day, day, day)
}
