import importlib
import os

from util.input import readInput, fetchInput, writeOutput, fetchExamples
from util.timed import timed

def call_execute(day, part, example):
    dayName = f"day{str(day).zfill(2)}"
    moduleName = f"{dayName}.run"
    module = importlib.import_module(moduleName)

    currentDir = os.path.dirname(os.path.abspath(__file__))
    dayDir = os.path.join(currentDir, dayName)

    if example:
        fetchExamples(day, dayDir)
    else:
        fetchInput(day, dayDir)

    print(f"year 2023, day {day}")

    if part == "0" or part == "1":
        inputFile = readInput(os.path.join(dayDir, "example.1" if example else "input"))
        result = timed(module.part1, inputFile)
        writeOutput(result, os.path.join(dayDir, "example.1.out" if example else "input.1.out"))
        print(result)

    if part == "0" or part == "2":
        inputFile = readInput(os.path.join(dayDir, "example.2" if example else "input"))
        result = timed(module.part2, inputFile)
        writeOutput(result, os.path.join(dayDir, "example.2.out" if example else "input.2.out"))
        print(result)

def main():
    day = os.getenv("DAY") or "1"
    example = os.getenv("EXAMPLE") or "F"
    part = os.getenv("PART") or "0"
    call_execute(day, part, example == "T")

if __name__ == "__main__":
    main()
