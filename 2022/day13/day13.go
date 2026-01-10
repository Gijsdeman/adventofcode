package main

import (
	"adventofcode/2022/core"
	"cmp"
	_ "embed"
	"encoding/json"
	"fmt"
	"sort"
	"strings"
)

//go:embed input
var input string

//go:embed example
var example string

type Day13 struct{}

var _ core.DayBase = Day13{}

func recursiveCompare(left any, right any) int {
	leftNum, leftIsNum := left.(float64)
	rightNum, rightIsNum := right.(float64)

	if leftIsNum && rightIsNum {
		return cmp.Compare(leftNum, rightNum)
	}

	leftSlice, leftIsSlice := left.([]any)
	if !leftIsSlice {
		leftSlice = []any{left}
	}

	rightSlice, rightIsSlice := right.([]any)
	if !rightIsSlice {
		rightSlice = []any{right}
	}

	for i := 0; i < len(leftSlice) && i < len(rightSlice); i++ {
		result := recursiveCompare(leftSlice[i], rightSlice[i])
		if result != 0 {
			return result
		}
	}
	return cmp.Compare(len(leftSlice), len(rightSlice))
}

func (d Day13) Part1(input string) string {
	defer core.Timer("Part 1")()

	sections := core.GetSections(strings.TrimSpace(input))
	correctOrders := 0

	for i, section := range sections {
		lines := core.GetLines(section, true)

		var left, right []any
		json.Unmarshal([]byte(lines[0]), &left)
		json.Unmarshal([]byte(lines[1]), &right)
		if recursiveCompare(left, right) == -1 {
			correctOrders += i + 1
		}
	}

	return fmt.Sprintf("%d", correctOrders)
}

func (d Day13) Part2(input string) string {
	defer core.Timer("Part 2")()

	lines := core.GetLines(strings.TrimSpace(input), true)

	var packets []any
	for _, line := range lines {
		var packet any
		json.Unmarshal([]byte(line), &packet)
		packets = append(packets, packet)
	}

	divider2 := []any{[]any{float64(2)}}
	divider6 := []any{[]any{float64(6)}}
	packets = append(packets, divider2, divider6)

	sort.Slice(packets, func(i, j int) bool {
		return recursiveCompare(packets[i], packets[j]) == -1
	})

	decoderKey := 1
	for i, packet := range packets {
		if recursiveCompare(packet, divider2) == 0 || recursiveCompare(packet, divider6) == 0 {
			decoderKey *= i + 1
		}
	}

	return fmt.Sprintf("%d", decoderKey)
}

func main() {
	core.RunDays(Day13{}, input, example)
}
