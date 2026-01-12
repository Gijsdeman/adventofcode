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

type Day18 struct{}

var _ core.DayBase = Day18{}

type cube struct {
	x, y, z int
}

func neighbors(c cube) []cube {
	return []cube{
		{c.x + 1, c.y, c.z},
		{c.x - 1, c.y, c.z},
		{c.x, c.y + 1, c.z},
		{c.x, c.y - 1, c.z},
		{c.x, c.y, c.z + 1},
		{c.x, c.y, c.z - 1},
	}
}

func inBounds(c cube, minX, maxX, minY, maxY, minZ, maxZ int) bool {
	return c.x >= minX && c.x <= maxX &&
		c.y >= minY && c.y <= maxY &&
		c.z >= minZ && c.z <= maxZ
}

func (d Day18) Part1(input string) string {
	defer core.Timer("Part 1")()

	lines := core.GetLines(strings.TrimSpace(input), true)
	cubes := util.NewSet[cube]()

	for _, line := range lines {
		coords := core.GetIntsFromLine(line)
		cube := cube{coords[0], coords[1], coords[2]}
		cubes.Add(cube)
	}	

	exposedSurface := 0;
	for _, cube := range cubes.Items() {
		for _, neighbor := range neighbors(cube) {
			if !cubes.Contains(neighbor) {
				exposedSurface++
			}
		}
	}

	return fmt.Sprintf("%d", exposedSurface)
}

func (d Day18) Part2(input string) string {
	defer core.Timer("Part 2")()

	lines := core.GetLines(strings.TrimSpace(input), true)
	cubes := util.NewSet[cube]()

	for _, line := range lines {
		coords := core.GetIntsFromLine(line)
		cube := cube{coords[0], coords[1], coords[2]}
		cubes.Add(cube)
	}

	minX, maxX := cubes.Items()[0].x-1, cubes.Items()[0].x+1
	minY, maxY := cubes.Items()[0].y-1, cubes.Items()[0].y+1
	minZ, maxZ := cubes.Items()[0].z-1, cubes.Items()[0].z+1

	for _, c := range cubes.Items() {
		minX = min(minX, c.x-1)
		maxX = max(maxX, c.x+1)
		minY = min(minY, c.y-1)
		maxY = max(maxY, c.y+1)
		minZ = min(minZ, c.z-1)
		maxZ = max(maxZ, c.z+1)
	}

	reachable := util.NewSet[cube]()
	queue := util.NewQueue[cube]()
	queue.Enqueue(cube{minX, minY, minZ})
	reachable.Add(queue.Peek())

	for !queue.IsEmpty() {
		current := queue.Dequeue()

		for _, neighbor := range neighbors(current) {
			if inBounds(neighbor, minX, maxX, minY, maxY, minZ, maxZ) &&
				!cubes.Contains(neighbor) &&
				!reachable.Contains(neighbor) {
				reachable.Add(neighbor)
				queue.Enqueue(neighbor)
			}
		}
	}

	exposedSurface := 0
	for _, cube := range cubes.Items() {
		for _, neighbor := range neighbors(cube) {
			if reachable.Contains(neighbor) {
				exposedSurface++
			}
		}
	}

	return fmt.Sprintf("%d", exposedSurface)
}

func main() {
	core.RunDays(Day18{}, input, example)
}
