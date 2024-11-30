import re

def isNeighbouring(lines, rows, columns, mapping, numberMatch, currentRow, checkStar):
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

def part1(file):
    lines = file.split('\n')
    rows = len(lines)
    columns = len(lines[0])
    mapping = {}

    result = 0
    for rowIndex in range(0, rows):
        for numberMatch in re.finditer("([0-9]+)", lines[rowIndex]):
            if isNeighbouring(lines, rows, columns, mapping, numberMatch, rowIndex, False):
                result += int(numberMatch.group())
    return result


def part2(file):
    lines = file.split('\n')
    rows = len(lines)
    columns = len(lines[0])
    mapping = {}

    for rowIndex in range(0, rows):
        for numberMatch in re.finditer("([0-9]+)", lines[rowIndex]):
            isNeighbouring(lines, rows, columns, mapping, numberMatch, rowIndex, True)

    return sum(int(star[0]) * int(star[1]) for star in mapping.values() if len(star) == 2)