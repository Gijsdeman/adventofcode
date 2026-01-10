package main

import (
	"adventofcode/2022/core"
	_ "embed"
	"fmt"
	"strconv"
	"strings"
)

//go:embed input
var input string

//go:embed example
var example string

type Day10 struct{}

var _ core.DayBase = Day10{}

func runOperations(operations []string, handleCycle func(cycle int, x int)) {
	cycle := 0
	x := 1
	for _, operation := range operations {
		if operation == "noop" {
			cycle++
			handleCycle(cycle, x)
		} else {
			value, _ := strconv.Atoi(operation[5:])

			cycle++
			handleCycle(cycle, x)

			cycle++
			handleCycle(cycle, x)

			x += value
		}
	}
}

func (d Day10) Part1(input string) string {
	defer core.Timer("Part 1")()

	operations := core.GetLines(input, true)
	result := 0

	checkSignal := func(cycle int, x int) {
		if (cycle-20)%40 == 0 {
			result += cycle * x
		}
	}
	runOperations(operations, checkSignal)

	return fmt.Sprintf("%d", result)
}

func (d Day10) Part2(input string) string {
	defer core.Timer("Part 2")()

	operations := core.GetLines(input, true)
	var screen strings.Builder

	drawPixel := func(cycle int, x int) {
		pixelPos := (cycle - 1) % 40

		if pixelPos >= x-1 && pixelPos <= x+1 {
			screen.WriteByte('#')
		} else {
			screen.WriteByte('.')
		}

		if pixelPos == 39 {
			screen.WriteByte('\n')
		}
	}
	runOperations(operations, drawPixel)

	return screen.String()
}

func main() {
	core.RunDays(Day10{}, input, example)
}
