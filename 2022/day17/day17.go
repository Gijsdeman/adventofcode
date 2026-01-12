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

type Day17 struct{}

var _ core.DayBase = Day17{}

type point struct {
	x, y int
}

type rock struct {
	points []point
}

type stateKey struct {
	rockId  int
	jetId   int
	heights [7]int
}

type cycleInfo struct {
	rockNum int
	height  int
}

var rocks = []rock{
	{points: []point{{0, 0}, {1, 0}, {2, 0}, {3, 0}}},
	{points: []point{{1, 0}, {0, 1}, {1, 1}, {2, 1}, {1, 2}}},
	{points: []point{{0, 0}, {1, 0}, {2, 0}, {2, 1}, {2, 2}}},
	{points: []point{{0, 0}, {0, 1}, {0, 2}, {0, 3}}},
	{points: []point{{0, 0}, {1, 0}, {0, 1}, {1, 1}}},
}

func parseInput(input string) []int {
	jets := make([]int, len(input))
	for i, c := range input {
		if c == '<' {
			jets[i] = -1
		} else {
			jets[i] = 1
		}
	}
	return jets
}

func getHeightDifferences(columnHeights [7]int) [7]int {
	var diffs [7]int
	diffs[0] = 0
	for i := 1; i < 7; i++ {
		diffs[i] = columnHeights[i] - columnHeights[i-1]
	}
	return diffs
}

func isCollision(rock rock, pos point, occupied map[point]bool) bool {
	for _, p := range rock.points {
		x := pos.x + p.x
		y := pos.y + p.y

		if x < 0 || x >= 7 || y < 0 || occupied[point{x, y}] {
			return true
		}
	}
	return false
}

func dropRock(
	rock rock,
	maxHeight int,
	jetIndex *int,
	jets []int,
	occupied map[point]bool,
	columnHeights *[7]int,
) int {
	pos := point{2, maxHeight + 3}

	for {
		jetDir := jets[*jetIndex%len(jets)]
		*jetIndex++
		newPos := point{pos.x + jetDir, pos.y}
		if !isCollision(rock, newPos, occupied) {
			pos = newPos
		}

		newPos = point{pos.x, pos.y - 1}
		if isCollision(rock, newPos, occupied) {
			newMaxHeight := maxHeight
			for _, p := range rock.points {
				x := pos.x + p.x
				y := pos.y + p.y
				occupied[point{x, y}] = true
				if y+1 > newMaxHeight {
					newMaxHeight = y + 1
				}
				if y+1 > columnHeights[x] {
					columnHeights[x] = y + 1
				}
			}
			return newMaxHeight
		}
		pos = newPos
	}
}

func simulateRockFall(jets []int, targetRocks int) int {
	occupied := make(map[point]bool)
	maxHeight := 0
	jetIndex := 0
	var columnHeights [7]int

	visited := make(map[stateKey]cycleInfo)

	for rockNum := range targetRocks {
		rock := rocks[rockNum%len(rocks)]
		maxHeight = dropRock(rock, maxHeight, &jetIndex, jets, occupied, &columnHeights)

		state := stateKey{
			rockId:  rockNum % len(rocks),
			jetId:   jetIndex % len(jets),
			heights: getHeightDifferences(columnHeights),
		}

		if prev, found := visited[state]; found {
			cycleLength := rockNum - prev.rockNum
			cycleHeight := maxHeight - prev.height

			remainingRocks := targetRocks - rockNum - 1
			fullCycles := remainingRocks / cycleLength
			remainder := remainingRocks % cycleLength

			for i := range remainder {
				rock := rocks[(rockNum+1+i)%len(rocks)]
				maxHeight = dropRock(rock, maxHeight, &jetIndex, jets, occupied, &columnHeights)
			}

			return maxHeight + (fullCycles * cycleHeight)
		}

		visited[state] = cycleInfo{rockNum, maxHeight}
	}

	return maxHeight
}

func (d Day17) Part1(input string) string {
	defer core.Timer("Part 1")()

	jets := parseInput(strings.TrimSpace(input))
	height := simulateRockFall(jets, 2022)

	return fmt.Sprintf("%d", height)
}

func (d Day17) Part2(input string) string {
	defer core.Timer("Part 2")()

	jets := parseInput(strings.TrimSpace(input))
	height := simulateRockFall(jets, 1000000000000)

	return fmt.Sprintf("%d", height)
}

func main() {
	core.RunDays(Day17{}, input, example)
}
