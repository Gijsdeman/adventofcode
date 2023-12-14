import timeit
import re

file = open('input', 'r').read().strip()
lines = file.split('\n')
grid = [[char for char in row] for row in lines]

rows = len(lines)
columns = len(lines[0])
mapping = {}


def isNeighbouring(numberMatch, currentRow, checkStar):
    locations = [(currentRow, numberMatch.start() - 1), (currentRow, numberMatch.end())]
    locations += [(currentRow - 1, currentColumn) for currentColumn in
                  range(numberMatch.start() - 1, numberMatch.end() + 1)]
    locations += [(currentRow + 1, currentColumn) for currentColumn in
                  range(numberMatch.start() - 1, numberMatch.end() + 1)]

    for row, column in locations:
        if 0 <= row < rows and 0 <= column < columns:
            if checkStar and lines[row][column] == '*':
                if (row, column) in mapping:
                    mapping[(row, column)].append(numberMatch.group())
                else:
                    mapping[(row, column)] = [numberMatch.group()]
            elif lines[row][column] != '.':
                return True
    return False


def part1():
    result = 0
    for rowIndex in range(0, rows):
        for numberMatch in re.finditer("([0-9]+)", lines[rowIndex]):
            if isNeighbouring(numberMatch, rowIndex, False):
                result += int(numberMatch.group())
    return result


def part2():
    for rowIndex in range(0, rows):
        for numberMatch in re.finditer("([0-9]+)", lines[rowIndex]):
            isNeighbouring(numberMatch, rowIndex, True)

    return sum(int(star[0]) * int(star[1]) for star in mapping.values() if len(star) == 2)


print("Part 1")
print(round(timeit.timeit('print(part1())', globals=globals(), number=1) * 1000, 4), 'ms\n')
print("Part 2")
print(round(timeit.timeit('print(part2())', globals=globals(), number=1) * 1000, 4), 'ms')
