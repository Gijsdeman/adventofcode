package main

import (
	"adventofcode/2022/core"
	_ "embed"
	"fmt"
	"strings"
)

//go:embed input
var input string

//go:embed example
var example string

type Day14 struct{}

var _ core.DayBase = Day14{}

type Position struct {
	x int
	y int
}

func parseInput(input string) (occupied map[Position]bool, maxY int) {
	borders := make(map[Position]bool)
	lines := core.GetLines(strings.TrimSpace(input), true)
	for _, line := range lines {
		coords := core.GetIntsFromLine(line)

		for i := 0; i < len(coords)-2; i += 2 {
			x1, y1 := coords[i], coords[i+1]
			x2, y2 := coords[i+2], coords[i+3]

			if x1 == x2 {
				minY, maxY := min(y1, y2), max(y1, y2)
				for y := minY; y <= maxY; y++ {
					borders[Position{x1, y}] = true
				}
			} else {
				minX, maxX := min(x1, x2), max(x1, x2)
				for x := minX; x <= maxX; x++ {
					borders[Position{x, y1}] = true
				}
			}
		}
	}

	for pos := range borders {
		if pos.y > maxY {
			maxY = pos.y
		}
	}

	occupied = make(map[Position]bool)
	for pos := range borders {
		occupied[pos] = true
	}

	return
}

func createOccupiedGrid(occupied map[Position]bool, maxY int, hasFloor bool) (int, [][]bool) {
	minX, maxX := 500, 500
	for pos := range occupied {
		if pos.x < minX {
			minX = pos.x
		}
		if pos.x > maxX {
			maxX = pos.x
		}
	}

	// add padding
	minX -= 200
	maxX += 200
	width := maxX - minX + 1
	height := maxY + 3

	grid := make([][]bool, height)
	for i := range grid {
		grid[i] = make([]bool, width)
	}

	for pos := range occupied {
		if pos.x >= minX && pos.x <= maxX {
			grid[pos.y][pos.x-minX] = true
		}
	}

	floorY := maxY + 2
	if hasFloor {
		for x := range width {
			grid[floorY][x] = true
		}
	}
	return minX, grid
}

func simulateSand(maxY int, occupied map[Position]bool, hasFloor bool) int {
	minX, grid := createOccupiedGrid(occupied, maxY, hasFloor)

	sandCount := 0
	for {
		if grid[0][500-minX] {
			return sandCount
		}

		sandX, sandY := 500, 0

		for {
			if !hasFloor && sandY > maxY {
				return sandCount
			}

			nextY := sandY + 1

			if !grid[nextY][sandX-minX] {
				sandY = nextY
				continue
			}

			if !grid[nextY][sandX-1-minX] {
				sandX--
				sandY = nextY
				continue
			}

			if !grid[nextY][sandX+1-minX] {
				sandX++
				sandY = nextY
				continue
			}

			grid[sandY][sandX-minX] = true
			sandCount++
			break
		}
	}
}

func (d Day14) Part1(input string) string {
	defer core.Timer("Part 1")()

	occupied, maxY := parseInput(input)
	sandCount := simulateSand(maxY, occupied, false)

	return fmt.Sprintf("%d", sandCount)
}

func (d Day14) Part2(input string) string {
	defer core.Timer("Part 2")()

	occupied, maxY := parseInput(input)
	sandCount := simulateSand(maxY, occupied, true)

	return fmt.Sprintf("%d", sandCount)
}

func main() {
	core.RunDays(Day14{}, input, example)
}
