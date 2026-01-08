package main

import (
	"adventofcode/2022/core"
	_ "embed"
	"fmt"
	"sort"
	"strconv"
	"strings"
)

//go:embed input
var input string

//go:embed example
var example string

type Day01 struct{}

var _ core.DayBase = Day01{}

func (d Day01) Part1(input string) string {
	defer core.Timer("Part 1")()

	sections := core.GetSections(strings.TrimSpace(input))
	result := 0

	for _, section := range sections {
		lines := strings.Split(section, "\n")
		carriedCalories := 0
		for _, line := range lines {
			calories, _ := strconv.Atoi(line)
			carriedCalories += calories
		}
		result = max(carriedCalories, result)
	}

	return fmt.Sprintf("%d", result)
}

func (d Day01) Part2(input string) string {
	defer core.Timer("Part 2")()

	sections := core.GetSections(strings.TrimSpace(input))
	var allCalories []int

	for _, section := range sections {
		lines := strings.Split(section, "\n")
		carriedCalories := 0
		for _, line := range lines {
			calories, _ := strconv.Atoi(line)
			carriedCalories += calories
		}
		allCalories = append(allCalories, carriedCalories)
	}

	sort.Sort(sort.Reverse(sort.IntSlice(allCalories)))
	result := allCalories[0] + allCalories[1] + allCalories[2]

	return fmt.Sprintf("%d", result)
}

func main() {
	core.RunDays(Day01{}, input, example)
}
