import timeit

file = open('input', 'r').read().strip()
lines = file.split('\n')
sections = file.split('\n\n')
grid = [[char for char in row] for row in lines]


def part1():
    result = 0
    for section in sections:
        grid = [[char for char in row] for row in section.split('\n')]
        height = len(grid)
        width = len(grid[0])

        for splittingRow in range(height - 1):
            # -1 to prevent double counting
            mirrored = True
            for delta in range(height):
                topIndex = splittingRow - delta
                bottomIndex = splittingRow + delta + 1
                if 0 <= topIndex < bottomIndex < height and grid[topIndex] != grid[bottomIndex]:
                    # If one of the lines does not match; break
                    mirrored = False
                    break
            if mirrored:
                result += (splittingRow + 1) * 100

        for splittingColumn in range(width - 1):
            # -1 to prevent double counting
            mirrored = True
            for delta in range(width):
                leftIndex = splittingColumn - delta
                rightIndex = splittingColumn + delta + 1
                if 0 <= leftIndex < rightIndex < width:
                    for row in range(height):
                        # If one of the characters does not match; break
                        if grid[row][leftIndex] != grid[row][rightIndex]:
                            mirrored = False
                            break
            if mirrored:
                result += splittingColumn + 1
    return result


def part2():
    result = 0
    for section in sections:
        grid = [[char for char in row] for row in section.split('\n')]
        height = len(grid)
        width = len(grid[0])

        for splittingRow in range(height - 1):
            # -1 to prevent double counting
            # count "smudges"
            epsilon = 0
            for delta in range(height):
                topIndex = splittingRow - delta
                bottomIndex = splittingRow + delta + 1
                if 0 <= topIndex < bottomIndex < height:
                    # Check every character on possible differences and count
                    for column in range(width):
                        if grid[topIndex][column] != grid[bottomIndex][column]:
                            epsilon += 1
            if epsilon == 1:
                result += (splittingRow + 1) * 100

        for splittingColumn in range(width - 1):
            # -1 to prevent double counting
            # count "smudges"
            epsilon = 0
            for delta in range(width):
                leftIndex = splittingColumn - delta
                rightIndex = splittingColumn + delta + 1
                if 0 <= leftIndex < rightIndex < width:
                    # Check every character on possible differences and count
                    for row in range(height):
                        if grid[row][leftIndex] != grid[row][rightIndex]:
                            epsilon += 1
            if epsilon == 1:
                result += splittingColumn + 1
    return result


print("Part 1")
print(round(timeit.timeit('print(part1())', globals=globals(), number=1) * 1000, 4), 'ms\n')
print("Part 2")
print(round(timeit.timeit('print(part2())', globals=globals(), number=1) * 1000, 4), 'ms')
