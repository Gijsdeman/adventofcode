package main

import (
	"adventofcode/2022/core"
	_ "embed"
	"fmt"
	"math"
	"strconv"
	"strings"
)

//go:embed input
var input string

//go:embed example
var example string

type Day07 struct{}

var _ core.DayBase = Day07{}

type Node struct {
	Name     string
	IsDir    bool
	Size     int
	Children map[string]*Node
	Parent   *Node
}

func calculateSizes(node *Node) int {
	if !node.IsDir {
		return node.Size
	}

	total := 0
	for _, child := range node.Children {
		total += calculateSizes(child)
	}
	node.Size = total
	return total
}

func buildFileTree(input string) *Node {
	root := &Node{Name: "/", IsDir: true, Children: make(map[string]*Node)}
	current := root

	lines := core.GetLines(strings.TrimSpace(input), true)
	for _, line := range lines[1:] {
		if line[0] == '$' {
			if strings.HasPrefix(line, "$ cd ") {
				dirName := line[5:]
				if dirName == ".." {
					current = current.Parent
				} else {
					if _, exists := current.Children[dirName]; !exists {
						current.Children[dirName] = &Node{
							Name:     dirName,
							IsDir:    true,
							Children: make(map[string]*Node),
							Parent:   current,
						}
					}
					current = current.Children[dirName]
				}
			}
		} else if !strings.HasPrefix(line, "dir ") {
			parts := strings.SplitN(line, " ", 2)
			size, _ := strconv.Atoi(parts[0])
			current.Children[parts[1]] = &Node{
				Name:   parts[1],
				IsDir:  false,
				Size:   size,
				Parent: current,
			}
		}
	}

	calculateSizes(root)
	return root
}

func dfs(node *Node, visit func(*Node)) {
	visit(node)
	for _, child := range node.Children {
		dfs(child, visit)
	}
}

func (d Day07) Part1(input string) string {
	defer core.Timer("Part 1")()

	root := buildFileTree(input)

	result := 0
	dfs(root, func(n *Node) {
		if n.IsDir && n.Size <= 100000 {
			result += n.Size
		}
	})

	return fmt.Sprintf("%d", result)
}

func (d Day07) Part2(input string) string {
	defer core.Timer("Part 2")()

	root := buildFileTree(input)

	spaceNeeded := 30000000 - (70000000 - root.Size)
	result := math.MaxInt

	dfs(root, func(n *Node) {
		if n.IsDir && n.Size >= spaceNeeded {
			result = min(result, n.Size)
		}
	})

	return fmt.Sprintf("%d", result)
}

func main() {
	core.RunDays(Day07{}, input, example)
}
