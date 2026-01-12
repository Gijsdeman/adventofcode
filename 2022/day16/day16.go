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

type Day16 struct{}

var _ core.DayBase = Day16{}

type valve struct {
	flowRate  int
	distances []int
}

type rawValve struct {
	flowRate int
	tunnels  []string
}

type searchKey struct {
	valve    int
	opened   uint64
	timeLeft int
}

type valveSet struct {
	mask     uint64
	pressure int
}

func bfs(start string, valveMap map[string]rawValve) map[string]int {
	dist := make(map[string]int)
	dist[start] = 0
	queue := []string{start}

	for len(queue) > 0 {
		u := queue[0]
		queue = queue[1:]
		for _, v := range valveMap[u].tunnels {
			if _, visited := dist[v]; !visited {
				dist[v] = dist[u] + 1
				queue = append(queue, v)
			}
		}
	}
	return dist
}

func parseValves(input string) ([]valve, int) {
	lines := core.GetLines(strings.TrimSpace(input), true)

	valveMap := make(map[string]rawValve)

	for _, line := range lines {
		parts := strings.Split(line, ";")
		name := parts[0][6:8]
		flowRate := core.GetIntsFromLine(parts[0])[0]

		tunnelsPart := strings.TrimSpace(parts[1])
		tunnelsPart = strings.TrimPrefix(tunnelsPart, "tunnels lead to valves ")
		tunnelsPart = strings.TrimPrefix(tunnelsPart, "tunnel leads to valve ")
		tunnels := strings.Split(tunnelsPart, ", ")

		valveMap[name] = rawValve{flowRate, tunnels}
	}

	nonZeroValves := []string{"AA"}
	for name, tv := range valveMap {
		if tv.flowRate > 0 {
			nonZeroValves = append(nonZeroValves, name)
		}
	}

	valves := make([]valve, len(nonZeroValves))
	for i, firstValve := range nonZeroValves {
		distances := bfs(firstValve, valveMap)

		compressedDist := make([]int, len(nonZeroValves))
		for j, secondValve := range nonZeroValves {
			compressedDist[j] = distances[secondValve]
		}

		valves[i] = valve{
			flowRate:  valveMap[firstValve].flowRate,
			distances: compressedDist,
		}
	}

	return valves, 0
}

func search(
	valveId int,
	opened uint64,
	timeLeft int,
	currentPressure int,
	valves []valve,
	visited map[searchKey]int,
	allStates map[uint64]int,
) int {
	if visited != nil {
		// part 1
		key := searchKey{valveId, opened, timeLeft}
		if val, ok := visited[key]; ok {
			return val
		}
	}

	if allStates != nil {
		// part 2
		if existing, ok := allStates[opened]; !ok || currentPressure > existing {
			allStates[opened] = currentPressure
		}
	}

	maxPressure := 0
	valve := &valves[valveId]

	for i := 1; i < len(valves); i++ {
		bit := uint64(1) << i
		if opened&bit == 0 {
			timeNeeded := valve.distances[i] + 1
			if timeLeft >= timeNeeded {
				newOpened := opened | bit
				newTime := timeLeft - timeNeeded
				newPressure := currentPressure + valves[i].flowRate*newTime

				if visited != nil {
					// part 1
					pressure := valves[i].flowRate * newTime
					pressure += search(i, newOpened, newTime, 0, valves, visited, nil)
					maxPressure = max(maxPressure, pressure)
				} 

				if allStates != nil {
					// part 2
					search(i, newOpened, newTime, newPressure, valves, nil, allStates)
				}
			}
		}
	}

	// part 1
	if visited != nil {
		key := searchKey{valveId, opened, timeLeft}
		visited[key] = maxPressure
	}

	return maxPressure
}

func (d Day16) Part1(input string) string {
	defer core.Timer("Part 1")()

	valves, startId := parseValves(input)
	visited := make(map[searchKey]int)

	result := search(startId, 0, 30, 0, valves, visited, nil)
	return fmt.Sprintf("%d", result)
}

func (d Day16) Part2(input string) string {
	defer core.Timer("Part 2")()

	valves, startId := parseValves(input)

	allStates := make(map[uint64]int)
	search(startId, 0, 26, 0, valves, nil, allStates)

	maxPressure := 0
	states := make([]valveSet, 0, len(allStates))

	for mask, pressure := range allStates {
		states = append(states, valveSet{mask, pressure})
	}

	for i := 0; i < len(states); i++ {
		for j := i; j < len(states); j++ {
			if states[i].mask&states[j].mask == 0 {
				total := states[i].pressure + states[j].pressure
				maxPressure = max(maxPressure, total)
			}
		}
	}

	return fmt.Sprintf("%d", maxPressure)
}

func main() {
	core.RunDays(Day16{}, input, example)
}
