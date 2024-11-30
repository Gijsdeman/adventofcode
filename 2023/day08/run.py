from math import gcd

def checkEnds(locationList):
    for key in locationList:
        if key[-1] != 'Z':
            return False
    return True


def part1(file):
    lines = file.split('\n')
    instruction = lines[0]
    mapping = {}

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


def part2(file):
    lines = file.split('\n')
    instruction = lines[0]
    mapping = {}

    for line in lines[2:]:
        location, tuple = line.split(" = ")
        tuple = tuple.replace("(", "").replace(")", "")
        tuple = tuple.split(", ")
        mapping[location] = tuple

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