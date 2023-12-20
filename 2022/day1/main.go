package main

import (
	_ "embed"
	"fmt"
	"github.com/Gijsdeman/adventofcode/2022/maths"
	"github.com/Gijsdeman/adventofcode/2022/util"
	"sort"
	"strconv"
	"strings"
)

//go:embed input
var input string
var sections []string
var lines []string

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
	for _, section := range sections {
		var lines = strings.Split(section, "\n")
		var carriedCalories = 0
		for _, line := range lines {
			var calories, _ = strconv.Atoi(line)
			carriedCalories += calories
		}
		result = maths.MaxInt(carriedCalories, result)
	}
	return result
}

func part2() (result int) {
	defer util.Timer("Part 2")()
	var allCalories []int
	for _, section := range sections {
		var lines = strings.Split(section, "\n")
		var carriedCalories = 0
		for _, line := range lines {
			var calories, _ = strconv.Atoi(line)
			carriedCalories += calories
		}
		allCalories = append(allCalories, carriedCalories)
	}
	sort.Sort(sort.Reverse(sort.IntSlice(allCalories)))
	result = allCalories[0] + allCalories[1] + allCalories[2]
	return result
}
