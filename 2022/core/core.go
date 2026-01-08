package core

import (
	"fmt"
	"os"
	"time"
)

// DayBase is the interface that all day solutions must implement
type DayBase interface {
	Part1(input string) string
	Part2(input string) string
}

// RunDays executes day solutions based on the PART environment variable
func RunDays(day DayBase, input string, example string) {
	selectedInput := SelectInput(input, example)

	part := "0"
	if partEnv := os.Getenv("PART"); partEnv != "" {
		part = partEnv
	}

	if part == "0" || part == "1" {
		fmt.Println(day.Part1(selectedInput))
	}
	if part == "0" || part == "2" {
		fmt.Println(day.Part2(selectedInput))
	}
}

// SelectInput returns example or input based on EXAMPLE env var
func SelectInput(input, example string) string {
	if os.Getenv("EXAMPLE") == "T" || os.Getenv("EXAMPLE") == "true" {
		return example
	}
	return input
}

// Timer returns a function that prints the elapsed time since the timer was started
func Timer(name string) func() {
	start := time.Now()
	return func() {
		fmt.Printf("%s\n%v\n", name, time.Since(start))
	}
}
