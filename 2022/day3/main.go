package main

import (
	_ "embed"
	"fmt"
	"github.com/Gijsdeman/adventofcode/2022/util"
	"strings"
)

//go:embed input
var input string
var sections []string
var lines []string

var playMap = make(map[string]string)
var scoreMap = make(map[string]int)

func init() {
	input = strings.TrimSpace(input)
	sections = strings.Split(input, "\n\n")
	lines = strings.Split(input, "\n")
}

func main() {
	fmt.Printf("%v\n\n", part1())
	fmt.Printf("%v", part2())
}

func part1() (result int) {
	defer util.Timer("Part 1")()

	for _, line := range lines {
		var length, bytes = len(line), []byte(line)
		var firstPart, secondPart = bytes[:length/2], bytes[length/2:]

		var matchChar byte
		for _, firstChar := range firstPart {
			for _, secondChar := range secondPart {
				if firstChar == secondChar {
					matchChar = secondChar
					break
				}
			}
		}

		var matchValue = int(matchChar)
		if matchValue <= 90 {
			result += matchValue - 38
		} else {
			result += matchValue - 96
		}
	}
	return result
}

func part2() (result int) {
	defer util.Timer("Part 2")()
	for lineIndex := 0; lineIndex < len(lines); lineIndex += 3 {
		var firstPart = []byte(lines[lineIndex])
		var secondPart = []byte(lines[lineIndex+1])
		var thirdPart = []byte(lines[lineIndex+2])

		intersect := util.IntersectHash(util.IntersectHash(firstPart, secondPart), thirdPart)
		var matchValue = int(intersect[0])
		if matchValue <= 90 {
			result += matchValue - 38
		} else {
			result += matchValue - 96
		}
	}
	return result
}
