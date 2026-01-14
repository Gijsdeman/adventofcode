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

type Day20 struct{}

var _ core.DayBase = Day20{}

type item struct {
	value int
	id    int
}

func findItem(items []item, value int) (int, item) {
	currentPos := -1
	for i, item := range items {
		if item.id == value {
			currentPos = i
			break
		}
	}
	return currentPos, items[currentPos]
}

func moveItem(slice []item, from, to int) {
	if from == to {
		return
	}

	item := slice[from]

	if from < to {
		copy(slice[from:to], slice[from+1:to+1])
	} else {
		copy(slice[to+1:from+1], slice[to:from])
	}

	slice[to] = item
}

func mix(items []item) {
	n := len(items)

	for originalId := range n {
		itemPos, item := findItem(items, originalId)

		if item.value == 0 {
			continue
		}

		newPos := (itemPos + item.value) % (n - 1)
		if newPos < 0 {
			newPos += n - 1
		}

		moveItem(items, itemPos, newPos)
	}
}

func getCoordinates(items []item) int {
	zeroPos := -1
	for i, item := range items {
		if item.value == 0 {
			zeroPos = i
			break
		}
	}

	n := len(items)
	pos1000 := (zeroPos + 1000) % n
	pos2000 := (zeroPos + 2000) % n
	pos3000 := (zeroPos + 3000) % n

	return items[pos1000].value + items[pos2000].value + items[pos3000].value
}

func (d Day20) Part1(input string) string {
	defer core.Timer("Part 1")()

	lines := core.GetLines(strings.TrimSpace(input), true)
	items := make([]item, len(lines))
	
	for i, line := range lines {
		value := core.GetIntsFromLine(line)[0]
		items[i] = item{value: value, id: i}
	}

	mix(items)
	result := getCoordinates(items)

	return fmt.Sprintf("%d", result)
}

func (d Day20) Part2(input string) string {
	defer core.Timer("Part 2")()

	lines := core.GetLines(strings.TrimSpace(input), true)
	items := make([]item, len(lines))
	decryptionKey := 811589153

	for i, line := range lines {
		value := core.GetIntsFromLine(line)[0]
		items[i] = item{value: value * decryptionKey, id: i}
	}

	for round := 0; round < 10; round++ {
		mix(items)
	}

	result := getCoordinates(items)

	return fmt.Sprintf("%d", result)
}

func main() {
	core.RunDays(Day20{}, input, example)
}