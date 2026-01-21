package main

import (
	"adventofcode/2022/core"
	_ "embed"
	"fmt"
	"strconv"
	"strings"
)

//go:embed input
var input string

//go:embed example
var example string

type Day21 struct{}

var _ core.DayBase = Day21{}

const (
	ADD operation = iota
	SUB
	MUL
	DIV
	EQ
)

type operation int

type node struct {
	name      string
	value     int
	children  []string
	operation operation
}

func (op operation) apply(op1, op2 int) int {
	switch op {
	case ADD:
		return op1 + op2
	case SUB:
		return op1 - op2
	case MUL:
		return op1 * op2
	case DIV:
		return op1 / op2
	case EQ:
		if op1 == op2 {
			return 0
		}
	}
	return op1
}

func parseInput(input string) map[string]*node {
	graph := make(map[string]*node)

	lines := core.GetLines(strings.TrimSpace(input), true)
	for _, line := range lines {
		parts := strings.Split(line, ": ")
		if len(parts) != 2 {
			continue
		}
		name := parts[0]
		right := parts[1]
		if n, err := strconv.Atoi(right); err == nil {
			graph[name] = &node{
				name:  name,
				value: n,
			}
		} else {
			opParts := strings.Split(right, " ")
			if len(opParts) != 3 {
				continue
			}
			var op operation
			switch opParts[1] {
			case "+":
				op = ADD
			case "-":
				op = SUB
			case "*":
				op = MUL
			case "/":
				op = DIV
			}
			graph[name] = &node{
				name:      name,
				children:  []string{opParts[0], opParts[2]},
				operation: op,
			}
		}
	}
	return graph
}

func topoSort(graph map[string]*node) []string {
	visited := make(map[string]bool)
	var order []string

	var visit func(string)
	visit = func(n string) {
		if visited[n] {
			return
		}
		visited[n] = true
		node := graph[n]
		for _, child := range node.children {
			visit(child)
		}
		order = append(order, n)
	}

	for name := range graph {
		visit(name)
	}

	return order
}

func evaluate(graph map[string]*node, name string) int {
	n := graph[name]
	if len(n.children) == 0 {
		return n.value
	}
	left := evaluate(graph, n.children[0])
	right := evaluate(graph, n.children[1])
	return n.operation.apply(left, right)
}

func difference(graph map[string]*node, humnValue int) int {
	graph["humn"].value = humnValue
	left := evaluate(graph, graph["root"].children[0])
	right := evaluate(graph, graph["root"].children[1])
	return left - right
}

func (d Day21) Part1(input string) string {
	defer core.Timer("Part 1")()

	return fmt.Sprintf("%d", evaluate(parseInput(input), "root"))
}

func (d Day21) Part2(input string) string {
	defer core.Timer("Part 2")()

	graph := parseInput(input)

	low := int(-1e15)
	high := int(1e15)
	for low <= high {
		mid := low + (high-low)/2
		diff := difference(graph, mid)
		if diff == 0 {
			return fmt.Sprintf("%d", mid)
		} else if diff > 0 {
			low = mid + 1
		} else {
			high = mid - 1
		}
	}

	return fmt.Sprintf("%d", 0)
}

func main() {
	core.RunDays(Day21{}, input, example)
}
