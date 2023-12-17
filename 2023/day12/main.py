import timeit

file = open('input', 'r').read().strip()
lines = file.split('\n')
sections = file.split('\n\n')
grid = [[char for char in row] for row in lines]

visited = {}
springs = ''
counts = []


def countArrangements(springIndex, countIndex, currentLength):
    if (springIndex, countIndex, currentLength) in visited:
        return visited[(springIndex, countIndex, currentLength)]

    # Base case
    # We need to check if we have reached a valid ending
    if springIndex == len(springs):
        # if we reached en of spring and counts, or we finished considering the last spring
        if ((countIndex == len(counts) and currentLength == 0) or
                (countIndex == len(counts) - 1 and counts[countIndex] == currentLength)):
            return 1
    else:
        # Step case
        # If current position in spring is . (we know a spring just ended)
        result = 0
        if springs[springIndex] == '.' or springs[springIndex] == '?':
            if currentLength == 0:
                # If the length was already 0, we continue
                result += countArrangements(springIndex + 1, countIndex, 0)
            elif countIndex < len(counts) and counts[countIndex] == currentLength:
                # If the length found matches wanted length
                result += countArrangements(springIndex + 1, countIndex + 1, 0)

        # If current char is a # or ? (we should always be in a single spring)
        if springs[springIndex] == '#' or springs[springIndex] == '?':
            # We move forward to the following position in the spring
            result += countArrangements(springIndex + 1, countIndex, currentLength + 1)

        # Save for easy lookup
        visited[(springIndex, countIndex, currentLength)] = result
        return result
    return 0


def part1():
    result = 0
    for line in lines:
        global springs, counts
        springs = line.split()[0]
        counts = list(map(lambda x: int(x), line.split()[1].split(',')))

        visited.clear()
        result += countArrangements(0, 0, 0)

    return result


def part2():
    result = 0
    for line in lines:
        global springs, counts
        singleSprings = line.split()[0]
        singleCounts = list(map(lambda x: int(x), line.split()[1].split(',')))

        visited.clear()
        counts = [x for _ in range(0, 5) for x in singleCounts]
        springs = '?'.join([singleSprings for _ in range(0, 5)])

        result += countArrangements(0, 0, 0)

    return result


print("Part 1")
print(round(timeit.timeit('print(part1())', globals=globals(), number=1) * 1000, 4), 'ms\n')
print("Part 2")
print(round(timeit.timeit('print(part2())', globals=globals(), number=1) * 1000, 4), 'ms')
