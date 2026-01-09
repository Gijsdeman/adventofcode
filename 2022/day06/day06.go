package main

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

type Day06 struct{}

var _ core.DayBase = Day06{}

func firstNUniqueWindow(s string, n int) int {
	charSet := make(map[rune]bool)
	left := 0

	for right, char := range s {
		for charSet[char] {
			delete(charSet, rune(s[left]))
			left++
		}
		charSet[char] = true

		if right-left+1 == n {
			return right + 1
		}
	}

	return 0
}

func (d Day06) Part1(input string) string {
	defer core.Timer("Part 1")()

	result := 0

	lines := core.GetLines(strings.TrimSpace(input), true)
	for _, line := range lines {
		result += firstNUniqueWindow(line, 4)
	}

	return fmt.Sprintf("%d", result)
}

func (d Day06) Part2(input string) string {
	defer core.Timer("Part 2")()

	result := 0

	lines := core.GetLines(strings.TrimSpace(input), true)
	for _, line := range lines {
		result += firstNUniqueWindow(line, 14)
	}

	return fmt.Sprintf("%d", result)
}

func main() {
	core.RunDays(Day06{}, input, example)
}
