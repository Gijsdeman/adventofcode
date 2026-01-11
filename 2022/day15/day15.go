package main

import (
	"adventofcode/2022/core"
	"adventofcode/2022/util"
	_ "embed"
	"fmt"
	"slices"
	"strings"
)

//go:embed input
var input string

//go:embed example
var example string

type Day15 struct{}

var _ core.DayBase = Day15{}

type Position struct {
	x int
	y int
}

type Interval struct {
	start, end int
}

func manhattanDistance(a, b Position) int {
	return util.Abs(a.x-b.x) + util.Abs(a.y-b.y)
}

func (d Day15) Part1(input string) string {
	defer core.Timer("Part 1")()

	lines := core.GetLines(strings.TrimSpace(input), true)

	intervals := []Interval{}
	beaconsOnRow := util.NewSet[int]()

	yTarget := 2000000
	for _, line := range lines {
		nums := core.GetIntsFromLine(line)
		sensor := Position{nums[0], nums[1]}
		beacon := Position{nums[2], nums[3]}

		if beacon.y == yTarget {
			beaconsOnRow.Add(beacon.x)
		}

		distance := manhattanDistance(sensor, beacon)
		yDist := util.Abs(sensor.y - yTarget)

		if yDist <= distance {
			xRange := distance - yDist
			intervals = append(intervals, Interval{sensor.x - xRange, sensor.x + xRange})
		}
	}

	slices.SortFunc(intervals, func(a, b Interval) int {
		return a.start - b.start
	})

	merged := []Interval{intervals[0]}
	for _, curr := range intervals[1:] {
		last := len(merged) - 1
		if merged[last].end < curr.start-1 {
			merged = append(merged, curr)
		} else {
			merged[last].end = max(merged[last].end, curr.end)
		}
	}

	count := 0
	for _, interval := range merged {
		count += interval.end - interval.start + 1
	}
	count -= beaconsOnRow.Size()

	return fmt.Sprintf("%d", count)
}

func (d Day15) Part2(input string) string {
	defer core.Timer("Part 2")()

	lines := core.GetLines(strings.TrimSpace(input), true)

	type Sensor struct {
		pos      Position
		distance int
	}
	sensors := []Sensor{}

	for _, line := range lines {
		nums := core.GetIntsFromLine(line)
		sensor := Position{nums[0], nums[1]}
		beacon := Position{nums[2], nums[3]}
		distance := manhattanDistance(sensor, beacon)
		sensors = append(sensors, Sensor{sensor, distance})
	}

	maxCoord := 4000000

	for _, sensor := range sensors {
		dist := sensor.distance + 1

		directions := [][2]int{{1, 1}, {-1, 1}, {-1, -1}, {1, -1}}
		corners := []Position{
			{sensor.pos.x, sensor.pos.y - dist},
			{sensor.pos.x + dist, sensor.pos.y},
			{sensor.pos.x, sensor.pos.y + dist},
			{sensor.pos.x - dist, sensor.pos.y},
		}

		for i, corner := range corners {
			dx, dy := directions[i][0], directions[i][1]
			x, y := corner.x, corner.y

			for range dist {
				if x >= 0 && x <= maxCoord && y >= 0 && y <= maxCoord {
					pos := Position{x, y}

					covered := false
					for _, other := range sensors {
						if manhattanDistance(pos, other.pos) <= other.distance {
							covered = true
							break
						}
					}

					if !covered {
						tuningFreq := x*4000000 + y
						return fmt.Sprintf("%d", tuningFreq)
					}
				}

				x += dx
				y += dy
			}
		}
	}

	return fmt.Sprintf("%d", 0)
}

func main() {
	core.RunDays(Day15{}, input, example)
}
