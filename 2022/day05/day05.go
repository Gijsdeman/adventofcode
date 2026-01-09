package main

import (
	"adventofcode/2022/core"
	"adventofcode/2022/util"
	_ "embed"
	"strconv"
	"strings"
)

//go:embed input
var input string

//go:embed example
var example string

type Day05 struct{}

var _ core.DayBase = Day05{}

func solveCrateMover(input string, moveFunc func([]*util.Stack[string], int, int, int)) string {
	sections := core.GetSections(input)

	crates := core.GetLines(sections[0], false)
	crateNumbers := crates[len(crates)-1]
	numStacks := int(crateNumbers[len(crateNumbers)-2] - '0')

	stacks := make([]*util.Stack[string], numStacks)
	for i := range stacks {
		stacks[i] = util.NewStack[string]()
	}

	for i := len(crates) - 2; i >= 0; i-- {
		crateLine := crates[i]
		for j := 0; j < len(crateLine); j += 4 {
			chunk := crateLine[j:min(j+4, len(crateLine))]
			if chunk[1] != ' ' {
				stacks[j/4].Push(string(chunk[1]))
			}
		}
	}

	operations := core.GetLines(sections[1], true)

	for _, operation := range operations {
		parts := strings.Fields(operation)
		count, _ := strconv.Atoi(parts[1])
		from, _ := strconv.Atoi(parts[3])
		to, _ := strconv.Atoi(parts[5])

		moveFunc(stacks, count, from, to)
	}

	var result strings.Builder
	for _, stack := range stacks {
		result.WriteString(string(stack.Peek()))
	}

	return result.String()
}

func (d Day05) Part1(input string) string {
	defer core.Timer("Part 1")()

	return solveCrateMover(input, func(stacks []*util.Stack[string], count, from, to int) {
		for i := 0; i < count; i++ {
			if stacks[from-1].IsEmpty() {
				break
			}
			movedCrate := stacks[from-1].Pop()
			stacks[to-1].Push(movedCrate)
		}
	})
}

func (d Day05) Part2(input string) string {
	defer core.Timer("Part 2")()

	return solveCrateMover(input, func(stacks []*util.Stack[string], count, from, to int) {
		movedCrates := stacks[from-1].PopN(count)
		util.Reverse(movedCrates)
		stacks[to-1].PushN(movedCrates)
	})
}

func main() {
	core.RunDays(Day05{}, input, example)
}
