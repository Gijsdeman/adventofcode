package core

import (
	"strconv"
	"strings"
)

// GetLines splits input into lines
func GetLines(input string, removeEmpty bool) []string {
	lines := strings.Split(input, "\n")
	if removeEmpty {
		var result []string
		for _, line := range lines {
			if line != "" {
				result = append(result, line)
			}
		}
		return result
	}
	return lines
}

// GetSections splits input into sections separated by blank lines
func GetSections(input string) []string {
	return strings.Split(input, "\n\n")
}

// GetCharGrid converts input into a 2D character array
func GetCharGrid(input string, removeEmpty bool) [][]rune {
	lines := GetLines(input, removeEmpty)
	grid := make([][]rune, len(lines))
	for i, line := range lines {
		grid[i] = []rune(line)
	}
	return grid
}

// GetIntsFromLine extracts all integers from a line (handles negative numbers)
func GetIntsFromLine(line string) []int {
	var result []int
	i := 0

	for i < len(line) {
		for i < len(line) && line[i] != '-' && (line[i] < '0' || line[i] > '9') {
			i++
		}
		if i >= len(line) {
			break
		}

		// Mark start of number
		start := i
		if line[i] == '-' {
			i++
		}

		// Collect digits
		for i < len(line) && line[i] >= '0' && line[i] <= '9' {
			i++
		}

		// Parse the number if we collected any digits
		if i > start && (line[start] != '-' || i > start+1) {
			if num, err := strconv.Atoi(line[start:i]); err == nil {
				result = append(result, num)
			}
		}
	}

	return result
}
