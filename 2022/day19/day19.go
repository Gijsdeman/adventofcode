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

type Day19 struct{}

var _ core.DayBase = Day19{}

type robotType int

const (
	ORE robotType = iota
	CLAY
	OBSIDIAN
	GEODE
)

type costs struct {
	ore int
	clay int
	obsidian int
}

type blueprint struct {
	id int
	oreRobotCost costs
	clayRobotCost costs
	obsidianRobotCost costs
	geodeRobotCost costs
	maxOreCost int
	maxClayCost int
	maxObsidianCost int
}

type inventory struct {
	ore int
	clay int
	obsidian int
	geodes int

	oreRobots int
	clayRobots int
	obsidianRobots int
	geodeRobots int
}

type state struct {
	timeLimit int
	inv inventory
}

type robotOption struct {
	rType robotType
	cost costs
	maxLimit int
}

func canAfford(cost costs, inv inventory) bool {
	return inv.ore >= cost.ore &&
		inv.clay >= cost.clay &&
		inv.obsidian >= cost.obsidian
}

func buyRobot(cost costs, inv inventory) inventory {
	inv.ore -= cost.ore
	inv.clay -= cost.clay
	inv.obsidian -= cost.obsidian
	return inv
}

func updateInventory(inv inventory) inventory {
	inv.ore += inv.oreRobots
	inv.clay += inv.clayRobots
	inv.obsidian += inv.obsidianRobots
	inv.geodes += inv.geodeRobots
	return inv
}

func (bp blueprint) getRobotOptions() []robotOption {
	return []robotOption{
		{GEODE, bp.geodeRobotCost, 999},
		{OBSIDIAN, bp.obsidianRobotCost, bp.maxObsidianCost},
		{CLAY, bp.clayRobotCost, bp.maxClayCost},
		{ORE, bp.oreRobotCost, bp.maxOreCost},
	}
}

func (inv inventory) getRobotCount(rType robotType) int {
	switch rType {
	case ORE:
		return inv.oreRobots
	case CLAY:
		return inv.clayRobots
	case OBSIDIAN:
		return inv.obsidianRobots
	case GEODE:
		return inv.geodeRobots
	}
	return 0
}

func (inv *inventory) incrementRobot(rType robotType) {
	switch rType {
	case ORE:
		inv.oreRobots++
	case CLAY:
		inv.clayRobots++
	case OBSIDIAN:
		inv.obsidianRobots++
	case GEODE:
		inv.geodeRobots++
	}
}

func getQualityLevel(blueprint blueprint, timeLimit int, inventory inventory, visited map[state]int, bestSoFar *int) int {
	if (timeLimit == 0) {
		return inventory.geodes
	}

	// early exit if cannot beat best so far
	maxPossibleGeodes := inventory.geodes + inventory.geodeRobots * timeLimit + (timeLimit * (timeLimit - 1) / 2)
	if maxPossibleGeodes <= *bestSoFar {
		return 0
	}

	// cap resources - improve memoization 
	inventory.ore = min(inventory.ore, timeLimit * blueprint.maxOreCost)
	inventory.clay = min(inventory.clay, timeLimit * blueprint.maxClayCost)
	inventory.obsidian = min(inventory.obsidian, timeLimit * blueprint.maxObsidianCost)

	key := state{timeLimit: timeLimit, inv: inventory}
	if prevGeodes, ok := visited[key]; ok {
		return prevGeodes
	}

	geodes := 0
	
	// always buy geode robot if possible
	if canAfford(blueprint.geodeRobotCost, inventory) {
		newInv := buyRobot(blueprint.geodeRobotCost, inventory)
		newInv = updateInventory(newInv)
		newInv.geodeRobots++
		geodes = getQualityLevel(blueprint, timeLimit-1, newInv, visited, bestSoFar)
		*bestSoFar = max(*bestSoFar, geodes)
		visited[key] = geodes
		return geodes
	}
	
	for _, robot := range blueprint.getRobotOptions() {
		if robot.rType == GEODE {
			continue
		}

		if canAfford(robot.cost, inventory) && inventory.getRobotCount(robot.rType) < robot.maxLimit {
			newInv := buyRobot(robot.cost, inventory)
			newInv = updateInventory(newInv)
			newInv.incrementRobot(robot.rType)
			result := getQualityLevel(blueprint, timeLimit-1, newInv, visited, bestSoFar)
			geodes = max(geodes, result)
			*bestSoFar = max(*bestSoFar, geodes)
		}
	}

	inventory = updateInventory(inventory)
	result := getQualityLevel(blueprint, timeLimit-1, inventory, visited, bestSoFar)
	geodes = max(geodes, result)
	*bestSoFar = max(*bestSoFar, geodes)

	visited[key] = geodes
	return geodes
}

func parseAndRunBlueprint(line string, timeLimit int) int {
	ints := core.GetIntsFromLine(line)
	bp := blueprint{
		id: ints[0],
		oreRobotCost: costs{ ore: ints[1] },
		clayRobotCost: costs{ ore: ints[2] },
		obsidianRobotCost: costs{ ore: ints[3], clay: ints[4] },
		geodeRobotCost: costs{ ore: ints[5], obsidian: ints[6] },
	}
	bp.maxOreCost = max(bp.oreRobotCost.ore, bp.clayRobotCost.ore, bp.obsidianRobotCost.ore, bp.geodeRobotCost.ore)
	bp.maxClayCost = max(bp.oreRobotCost.clay, bp.clayRobotCost.clay, bp.obsidianRobotCost.clay, bp.geodeRobotCost.clay)
	bp.maxObsidianCost = max(bp.oreRobotCost.obsidian, bp.clayRobotCost.obsidian, bp.obsidianRobotCost.obsidian, bp.geodeRobotCost.obsidian)
	
	bestSoFar := 0
	return getQualityLevel(bp, timeLimit, inventory{
		oreRobots: 1,
	}, map[state]int{}, &bestSoFar)
}

func (d Day19) Part1(input string) string {
	defer core.Timer("Part 1")()

	qualityLevel := 1
	for i, line := range core.GetLines(input, true) {
		qualityLevel += (i + 1) * parseAndRunBlueprint(line, 24)
	}

	return fmt.Sprintf("%d", qualityLevel)
}

func (d Day19) Part2(input string) string {
	defer core.Timer("Part 2")()

	qualityLevel := 1
	for i, line := range core.GetLines(input, true) {
		qualityLevel *= parseAndRunBlueprint(line, 32)
		if i == 2 {
			break
		}
	}

	return fmt.Sprintf("%d", qualityLevel)
}

func main() {
	core.RunDays(Day19{}, input, example)
}
