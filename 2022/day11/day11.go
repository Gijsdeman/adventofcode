package main

import (
	"adventofcode/2022/core"
	_ "embed"
	"fmt"
	"sort"
	"strconv"
	"strings"
)

//go:embed input
var input string

//go:embed example
var example string

type Day11 struct{}

var _ core.DayBase = Day11{}

type Monkey struct {
	Items          []int
	Operation      func(int) int
	TestDivisor    int
	IfTrue         int
	IfFalse        int
	TotalInspected int
}

func ParseMonkeyOperation(sections []string) (monkeys []Monkey) {
	monkeys = make([]Monkey, len(sections))
	for monkeyIndex, monkeyInstruction := range sections {
		lines := core.GetLines(monkeyInstruction, true)
		currentMonkey := &monkeys[monkeyIndex]
		currentMonkey.Items = core.GetIntsFromLine(lines[1])

		operationLine := lines[2]
		currentMonkey.Operation = func(old int) int {
			parts := strings.Fields(operationLine)
			op := parts[4]
			valueStr := parts[5]
			var value int
			if valueStr == "old" {
				value = old
			} else {
				value, _ = strconv.Atoi(valueStr)
			}
			switch op {
			case "*":
				return old * value
			case "+":
				return old + value
			}
			return old
		}
		currentMonkey.TestDivisor = core.GetIntsFromLine(lines[3])[0]
		currentMonkey.IfTrue = core.GetIntsFromLine(lines[4])[0]
		currentMonkey.IfFalse = core.GetIntsFromLine(lines[5])[0]
	}
	return
}

func HandleMonkeyTurn(monkeys []Monkey, rounds int, worryDivisor int, useLCM bool, lcm int) {
	for range rounds {
		for i := range monkeys {
			currentMonkey := &monkeys[i]
			for _, item := range currentMonkey.Items {
				currentMonkey.TotalInspected++
				newWorry := currentMonkey.Operation(item)

				if useLCM {
					newWorry %= lcm
				} else {
					newWorry /= worryDivisor
				}

				if newWorry%currentMonkey.TestDivisor == 0 {
					monkeys[currentMonkey.IfTrue].Items = append(monkeys[currentMonkey.IfTrue].Items, newWorry)
				} else {
					monkeys[currentMonkey.IfFalse].Items = append(monkeys[currentMonkey.IfFalse].Items, newWorry)
				}
			}
			currentMonkey.Items = []int{}
		}
	}
}

func (d Day11) Part1(input string) string {
	defer core.Timer("Part 1")()

	sections := core.GetSections(strings.TrimSpace(input))
	monkeys := ParseMonkeyOperation(sections)

	HandleMonkeyTurn(monkeys, 20, 3, false, 0)

	sort.Slice(monkeys, func(i, j int) bool {
		return monkeys[i].TotalInspected > monkeys[j].TotalInspected
	})
	monkeyBusiness := monkeys[0].TotalInspected * monkeys[1].TotalInspected

	return fmt.Sprintf("%d", monkeyBusiness)
}

func (d Day11) Part2(input string) string {
	defer core.Timer("Part 2")()

	sections := core.GetSections(strings.TrimSpace(input))
	monkeys := ParseMonkeyOperation(sections)

	lcm := 1
	for _, m := range monkeys {
		lcm *= m.TestDivisor
	}

	HandleMonkeyTurn(monkeys, 10000, 0, true, lcm)

	sort.Slice(monkeys, func(i, j int) bool {
		return monkeys[i].TotalInspected > monkeys[j].TotalInspected
	})
	monkeyBusiness := monkeys[0].TotalInspected * monkeys[1].TotalInspected

	return fmt.Sprintf("%d", monkeyBusiness)
}

func main() {
	core.RunDays(Day11{}, input, example)
}
