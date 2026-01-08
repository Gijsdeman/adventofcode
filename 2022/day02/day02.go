package main

import (
	"adventofcode/2022/core"
	"adventofcode/2022/util"
	_ "embed"
	"fmt"
	"strings"
)

//go:embed input
var input string

//go:embed example
var example string

var playMap = map[string]string{
	"X": "A",
	"Y": "B",
	"Z": "C",
}

var scoreMap = map[string]int{
	"A": 1,
	"B": 2,
	"C": 3,
}

type Day02 struct{}

var _ core.DayBase = Day02{}

func (d Day02) Part1(input string) string {
	defer core.Timer("Part 1")()

	lines := core.GetLines(strings.TrimSpace(input), true)
	result := 0

	winMap := map[string]string{
		"A": "B",
		"B": "C",
		"C": "A",
	}

	for _, line := range lines {
		plays := strings.Fields(line)
		play, response := plays[0], playMap[plays[1]]
		result += scoreMap[response]

		if response == winMap[play] {
			result += 6
		} else if play == response {
			result += 3
		}
	}

	return fmt.Sprintf("%d", result)
}

func (d Day02) Part2(input string) string {
	defer core.Timer("Part 2")()

	lines := core.GetLines(strings.TrimSpace(input), true)
	result := 0

	winMap := map[string]string{
		"A": "B",
		"B": "C",
		"C": "A",
	}
	loseMap := util.ReverseMap(winMap)

	for _, line := range lines {
		plays := strings.Fields(line)
		play, response := plays[0], plays[1]

		if response == "X" {
			result += scoreMap[loseMap[play]]
		} else if response == "Y" {
			result += scoreMap[play] + 3
		} else {
			result += scoreMap[winMap[play]] + 6
		}
	}

	return fmt.Sprintf("%d", result)
}

func main() {
	core.RunDays(Day02{}, input, example)
}
