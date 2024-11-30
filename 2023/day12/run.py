# lines = file.split('\n')
# sections = file.split('\n\n')
# grid = [[char for char in row] for row in lines]

# visited = {}
# springs = ''
# counts = []


def countArrangements(springIndex, countIndex, currentLength, springs, counts, visited):
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
                result += countArrangements(springIndex + 1, countIndex, 0, springs, counts, visited)
            elif countIndex < len(counts) and counts[countIndex] == currentLength:
                # If the length found matches wanted length
                result += countArrangements(springIndex + 1, countIndex + 1, 0, springs, counts, visited)

        # If current char is a # or ? (we should always be in a single spring)
        if springs[springIndex] == '#' or springs[springIndex] == '?':
            # We move forward to the following position in the spring
            result += countArrangements(springIndex + 1, countIndex, currentLength + 1, springs, counts, visited)

        # Save for easy lookup
        visited[(springIndex, countIndex, currentLength)] = result
        return result
    return 0


def part1(file):
    lines = file.split('\n')

    visited = {}
    springs = ''
    counts = []

    result = 0
    for line in lines:
        springs = line.split()[0]
        counts = list(map(lambda x: int(x), line.split()[1].split(',')))

        visited.clear()
        result += countArrangements(0, 0, 0, springs, counts, visited)

    return result


def part2(file):
    lines = file.split('\n')

    visited = {}
    springs = ''
    counts = []

    result = 0
    for line in lines:
        singleSprings = line.split()[0]
        singleCounts = list(map(lambda x: int(x), line.split()[1].split(',')))

        visited.clear()
        counts = [x for _ in range(0, 5) for x in singleCounts]
        springs = '?'.join([singleSprings for _ in range(0, 5)])

        result += countArrangements(0, 0, 0, springs, counts, visited)

    return result