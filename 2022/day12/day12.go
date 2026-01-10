package main

import (
	"adventofcode/2022/core"
	"adventofcode/2022/util"
	_ "embed"
	"fmt"
	"math"
	"slices"
)

//go:embed input
var input string

//go:embed example
var example string

type Day12 struct{}

var _ core.DayBase = Day12{}

type Position struct {
	x int
	y int
}

var directions = []Position{{1, 0}, {-1, 0}, {0, 1}, {0, -1}}

func findShortestTrail(grid [][]rune, startPos Position, endPositions []Position) int {
	height := len(grid)
	width := len(grid[0])

	visited := make([][]int, height)
	for i := range visited {
		visited[i] = make([]int, width)
	}

	visited[startPos.x][startPos.y] = 1
	queue := util.Queue[Position]{}
	queue.Enqueue(startPos)

	for !queue.IsEmpty() {
		currentPos := queue.Dequeue()
		currentSteps := visited[currentPos.x][currentPos.y] - 1

		if slices.Contains(endPositions, currentPos) {
			return currentSteps
		}

		currentHeight := grid[currentPos.x][currentPos.y]

		for _, offset := range directions {
			nextPos := Position{currentPos.x + offset.x, currentPos.y + offset.y}
			nextHeight := grid[nextPos.x][nextPos.y]

			if currentHeight <= nextHeight+1 && visited[nextPos.x][nextPos.y] == 0 {
				visited[nextPos.x][nextPos.y] = currentSteps + 2 // +2 because we offset by 1
				queue.Enqueue(nextPos)
			}
		}
	}

	return math.MaxInt32
}

func parseGrid(input string, endRunes []rune) (grid [][]rune, startPos Position, endPositions []Position) {
	grid = core.GetCharGrid(input, true)
	grid = util.AddBorder(grid, 'A')

	for i := range grid {
		for j := range grid[i] {
			current := grid[i][j]

			if slices.Contains(endRunes, current) {
				endPositions = append(endPositions, Position{x: i, y: j})
			}

			switch current {
			case 'S':
				grid[i][j] = 'a'
			case 'E':
				startPos = Position{x: i, y: j}
				grid[i][j] = 'z'
			}
		}
	}

	return
}

func (d Day12) Part1(input string) string {
	defer core.Timer("Part 1")()

	grid, startPos, endPositions := parseGrid(input, []rune{'S'})
	steps := findShortestTrail(grid, startPos, endPositions)

	return fmt.Sprintf("%d", steps)
}

func (d Day12) Part2(input string) string {
	defer core.Timer("Part 2")()

	grid, startPos, endPositions := parseGrid(input, []rune{'S', 'a'})
	steps := findShortestTrail(grid, startPos, endPositions)

	return fmt.Sprintf("%d", steps)
}

func main() {
	core.RunDays(Day12{}, input, example)
}
