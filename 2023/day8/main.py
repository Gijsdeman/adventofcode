import timeit
from math import gcd

file = open('input', 'r').read().strip()
lines = file.split('\n')
print(lines)
sections = file.split('\n\n')
grid = [[char for char in row] for row in lines]

mapping = {}
instruction = lines[0]


def checkEnds(locationList):
    for key in locationList:
        if key[-1] != 'Z':
            return False
    return True


def part1():
    result = 0

    for line in lines[2:]:
        location, tuple = line.split(" = ")
        tuple = tuple.replace("(", "").replace(")", "")
        tuple = tuple.split(", ")
        mapping[location] = tuple

    current = 'AAA'
    directionIndex = 0
    while current != 'ZZZ':
        currentTuple = mapping[current]
        current = currentTuple[0 if instruction[directionIndex] == 'L' else 1]
        directionIndex += 1
        directionIndex %= len(instruction)
        result += 1

    return result


def part2():
    currentList = []
    for key in mapping.keys():
        if key[-1] == 'A':
            currentList.append(key)

    results = []
    for (startIndex, start) in enumerate(currentList):
        results.append(0)
        current = start
        directionIndex = 0
        while current[-1] != 'Z':
            currentTuple = mapping[current]
            current = currentTuple[0 if instruction[directionIndex] == 'L' else 1]
            directionIndex += 1
            directionIndex %= len(instruction)
            results[startIndex] += 1

    # Calculate least common multiple
    result = 1
    for item in results:
        result = result * item // gcd(result, item)

    return result


print("Part 1")
print(round(timeit.timeit('print(part1())', globals=globals(), number=1) * 1000, 4), 'ms\n')
print("Part 2")
print(round(timeit.timeit('print(part2())', globals=globals(), number=1) * 1000, 4), 'ms')