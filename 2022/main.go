package main

import (
	"fmt"
	"os"
	"os/exec"
	"path/filepath"
	"strconv"
	"strings"

	"adventofcode/2022/core"
)

func main() {
	dayEnv := getEnv("DAY", "0")
	partEnv := getEnv("PART", "0")
	exampleEnv := getEnv("EXAMPLE", "F")
	cwdEnv := getEnv("CWD", ".")
	sessionCookie := getEnv("SESSION", "")

	day, err := strconv.Atoi(dayEnv)
	if err != nil || day < 1 || day > 25 {
		fmt.Printf("Invalid DAY environment variable: %s\n", dayEnv)
		return
	}

	part, err := strconv.Atoi(partEnv)
	if err != nil || part < 0 || part > 2 {
		fmt.Printf("Invalid PART environment variable: %s\n", partEnv)
		return
	}

	if exampleEnv != "T" && exampleEnv != "F" {
		fmt.Printf("Invalid EXAMPLE environment variable: %s\n", exampleEnv)
		return
	}

	if sessionCookie == "" {
		fmt.Println("Set SESSION environment variable to fetch inputs")
		return
	}

	dayFolder := fmt.Sprintf("day%02d", day)
	dayFile := filepath.Join(cwdEnv, dayFolder, fmt.Sprintf("day%02d.go", day))
	outputType := "input"
	if exampleEnv == "T" {
		outputType = "example"
	}
	inputPath := filepath.Join(cwdEnv, dayFolder, outputType)

	fmt.Printf("year 2022, day %d\n", day)

	if !fileExists(dayFile) {
		if err := core.GenerateDay(day, cwdEnv, sessionCookie, 2022); err != nil {
			fmt.Printf("Failed to generate day: %v\n", err)
		}
		return
	}

	if exampleEnv == "F" && !fileExists(inputPath) {
		fetcher := core.NewInputFetcher(sessionCookie, 2022)
		if err := fetcher.FetchAndSaveInput(day, inputPath); err != nil {
			fmt.Printf("Failed to fetch input: %v\n", err)
		}
	}

	if err := runDay(cwdEnv, dayFolder, inputPath, part); err != nil {
		fmt.Printf("Failed to run day: %v\n", err)
	}
}

func getEnv(key, defaultValue string) string {
	if value := os.Getenv(key); value != "" {
		return value
	}
	return defaultValue
}

func fileExists(path string) bool {
	_, err := os.Stat(path)
	return err == nil
}

func runDay(workspaceRoot, dayFolder, inputPath string, part int) error {
	dayPath := filepath.Join(workspaceRoot, dayFolder)

	// Read the input file
	input, err := os.ReadFile(inputPath)
	if err != nil {
		return fmt.Errorf("failed to read input: %w", err)
	}

	// Run go run with the input embedded
	cmd := exec.Command("go", "run", ".")
	cmd.Dir = dayPath
	cmd.Stdout = os.Stdout
	cmd.Stderr = os.Stderr
	cmd.Stdin = strings.NewReader(string(input))

	// Set environment for part selection if needed
	cmd.Env = append(os.Environ(), fmt.Sprintf("PART=%d", part))

	return cmd.Run()
}
