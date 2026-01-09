package main

import (
	"adventofcode/2022/core"
	"adventofcode/2022/util"
	_ "embed"
	"fmt"
	"strconv"
	"strings"
)

//go:embed input
var input string

//go:embed example
var example string

type Day09 struct{}

var _ core.DayBase = Day09{}

type Position struct {
	x int
	y int
}

func moveKnot(head, tail Position) Position {
	dx := head.x - tail.x
	dy := head.y - tail.y

	if util.Abs(dx) <= 1 && util.Abs(dy) <= 1 {
		return tail
	}

	newTail := tail
	if dx != 0 {
		newTail.x += dx / util.Abs(dx)
	}
	if dy != 0 {
		newTail.y += dy / util.Abs(dy)
	}

	return newTail
}

func simulateRope(operations []string, knotCount int) int {
	knots := make([]Position, knotCount)
	for i := range knots {
		knots[i] = Position{0, 0}
	}

	visited := util.NewSet[Position]()
	visited.Add(knots[knotCount-1])

	for _, operation := range operations {
		dir := operation[0]
		count, _ := strconv.Atoi(operation[2:])

		for range count {
			switch dir {
			case 'U':
				knots[0].y++
			case 'D':
				knots[0].y--
			case 'L':
				knots[0].x--
			case 'R':
				knots[0].x++
			}

			for j := 1; j < knotCount; j++ {
				knots[j] = moveKnot(knots[j-1], knots[j])
			}

			visited.Add(knots[knotCount-1])
		}
	}

	return visited.Size()
}

func (d Day09) Part1(input string) string {
	defer core.Timer("Part 1")()
	operations := core.GetLines(strings.TrimSpace(input), true)
	return fmt.Sprintf("%d", simulateRope(operations, 2))
}

func (d Day09) Part2(input string) string {
	defer core.Timer("Part 2")()
	operations := core.GetLines(strings.TrimSpace(input), true)
	return fmt.Sprintf("%d", simulateRope(operations, 10))
}

func main() {
	core.RunDays(Day09{}, input, example)
}
