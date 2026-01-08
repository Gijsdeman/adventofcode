package core

import "strings"

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
