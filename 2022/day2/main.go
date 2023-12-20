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

	playMap["X"] = "A"
	playMap["Y"] = "B"
	playMap["Z"] = "C"

	scoreMap["A"] = 1
	scoreMap["B"] = 2
	scoreMap["C"] = 3
}

func main() {
	fmt.Printf("%v\n\n", part1())
	fmt.Printf("%v", part2())
}

func part1() (result int) {
	defer util.Timer("Part 1")()

	var winMap = make(map[string]string)
	winMap["A"] = "B"
	winMap["B"] = "C"
	winMap["C"] = "A"

	var plays []string
	var play, response string
	for _, line := range lines {
		plays = strings.Fields(line)
		play, response = plays[0], playMap[plays[1]]
		result += scoreMap[response]

		if response == winMap[play] {
			result += 6
		} else if play == response {
			result += 3
		}
	}
	return result
}

func part2() (result int) {
	defer util.Timer("Part 2")()
	var winMap = make(map[string]string)
	winMap["A"] = "B"
	winMap["B"] = "C"
	winMap["C"] = "A"
	var loseMap = util.ReverseMap(winMap)

	var plays []string
	var play, response string
	for _, line := range lines {
		plays = strings.Fields(line)
		play, response = plays[0], plays[1]

		if response == "X" {
			result += scoreMap[loseMap[play]]
		} else if response == "Y" {
			result += scoreMap[play] + 3
		} else {
			result += scoreMap[winMap[play]] + 6
		}
	}
	return result
}
