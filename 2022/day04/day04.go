package main

import (
	"adventofcode/2022/core"
	_ "embed"
	"strconv"
	"strings"
)

//go:embed input
var input string

//go:embed example
var example string

type Day04 struct{}

var _ core.DayBase = Day04{}

func countMatches(input string, predicate func(firstLower, firstHigher, secondLower, secondHigher int) bool) int {
	lines := core.GetLines(input, true)
	result := 0

	for _, line := range lines {
		parts := strings.FieldsFunc(line, func(r rune) bool {
			return r == ',' || r == '-'
		})

		firstLower, _ := strconv.Atoi(parts[0])
		firstHigher, _ := strconv.Atoi(parts[1])
		secondLower, _ := strconv.Atoi(parts[2])
		secondHigher, _ := strconv.Atoi(parts[3])

		if predicate(firstLower, firstHigher, secondLower, secondHigher) {
			result++
		}
	}

	return result
}

func (d Day04) Part1(input string) string {
	defer core.Timer("Part 1")()

	result := countMatches(input, func(firstLower, firstHigher, secondLower, secondHigher int) bool {
		return (secondLower <= firstLower && firstHigher <= secondHigher) ||
			(firstLower <= secondLower && secondHigher <= firstHigher)
	})

	return strconv.Itoa(result)
}

func (d Day04) Part2(input string) string {
	defer core.Timer("Part 2")()

	result := countMatches(input, func(firstLower, firstHigher, secondLower, secondHigher int) bool {
		return firstLower <= secondHigher && secondLower <= firstHigher
	})

	return strconv.Itoa(result)
}

func main() {
	core.RunDays(Day04{}, input, example)
}
