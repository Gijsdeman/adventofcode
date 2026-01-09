package main

import (
	"adventofcode/2022/core"
	_ "embed"
	"fmt"
)

//go:embed input
var input string

//go:embed example
var example string

type Day08 struct{}

var _ core.DayBase = Day08{}

func (d Day08) Part1(input string) string {
	defer core.Timer("Part 1")()

	grid := core.GetCharGrid(input, true)
	rows, cols := len(grid), len(grid[0])

	visible := make([][]bool, rows)
	for i := range visible {
		visible[i] = make([]bool, cols)
	}
	count := 0

	for r := range rows {
		maxHeight := -1
		for c := range cols {
			height := int(grid[r][c] - '0')
			if height > maxHeight {
				if !visible[r][c] {
					visible[r][c] = true
					count++
				}
				maxHeight = height
				if maxHeight == 9 {
					break
				}
			}
		}
		maxHeight = -1
		for c := cols - 1; c >= 0; c-- {
			height := int(grid[r][c] - '0')
			if height > maxHeight {
				if !visible[r][c] {
					visible[r][c] = true
					count++
				}
				maxHeight = height
				if maxHeight == 9 {
					break
				}
			}
		}
	}

	for c := range cols {
		maxHeight := -1
		for r := range rows {
			height := int(grid[r][c] - '0')
			if height > maxHeight {
				if !visible[r][c] {
					visible[r][c] = true
					count++
				}
				maxHeight = height
				if maxHeight == 9 {
					break
				}
			}
		}
		maxHeight = -1
		for r := rows - 1; r >= 0; r-- {
			height := int(grid[r][c] - '0')
			if height > maxHeight {
				if !visible[r][c] {
					visible[r][c] = true
					count++
				}
				maxHeight = height
				if maxHeight == 9 {
					break
				}
			}
		}
	}

	return fmt.Sprintf("%d", count)
}

func (d Day08) Part2(input string) string {
	defer core.Timer("Part 2")()

	grid := core.GetCharGrid(input, true)
	rows, cols := len(grid), len(grid[0])

	maxScore := 0

	for r := 1; r < rows-1; r++ {
		for c := 1; c < cols-1; c++ {
			height := int(grid[r][c] - '0')

			leftScore := 0
			for i := c - 1; i >= 0; i-- {
				leftScore++
				if int(grid[r][i]-'0') >= height {
					break
				}
			}

			rightScore := 0
			for i := c + 1; i < cols; i++ {
				rightScore++
				if int(grid[r][i]-'0') >= height {
					break
				}
			}

			upScore := 0
			for i := r - 1; i >= 0; i-- {
				upScore++
				if int(grid[i][c]-'0') >= height {
					break
				}
			}

			downScore := 0
			for i := r + 1; i < rows; i++ {
				downScore++
				if int(grid[i][c]-'0') >= height {
					break
				}
			}

			score := leftScore * rightScore * upScore * downScore
			maxScore = max(maxScore, score)
		}
	}

	return fmt.Sprintf("%d", maxScore)
}

func main() {
	core.RunDays(Day08{}, input, example)
}
