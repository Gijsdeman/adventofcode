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

type Day03 struct{}

var _ core.DayBase = Day03{}

func (d Day03) Part1(input string) string {
	defer core.Timer("Part 1")()

	lines := core.GetLines(strings.TrimSpace(input), true)
	result := 0

	for _, line := range lines {
		length, bytes := len(line), []byte(line)
		firstPart, secondPart := bytes[:length/2], bytes[length/2:]

		var matchChar byte
		for _, firstChar := range firstPart {
			for _, secondChar := range secondPart {
				if firstChar == secondChar {
					matchChar = secondChar
					break
				}
			}
		}

		matchValue := int(matchChar)
		if matchValue <= 90 {
			result += matchValue - 38
		} else {
			result += matchValue - 96
		}
	}

	return fmt.Sprintf("%d", result)
}

func (d Day03) Part2(input string) string {
	defer core.Timer("Part 2")()

	lines := core.GetLines(strings.TrimSpace(input), true)
	result := 0

	for lineIndex := 0; lineIndex < len(lines); lineIndex += 3 {
		firstPart := []byte(lines[lineIndex])
		secondPart := []byte(lines[lineIndex+1])
		thirdPart := []byte(lines[lineIndex+2])

		intersect := util.IntersectHash(util.IntersectHash(firstPart, secondPart), thirdPart)
		matchValue := int(intersect[0])
		if matchValue <= 90 {
			result += matchValue - 38
		} else {
			result += matchValue - 96
		}
	}

	return fmt.Sprintf("%d", result)
}

func main() {
	core.RunDays(Day03{}, input, example)
}
