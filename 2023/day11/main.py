import timeit

file = open('input', 'r').read().strip()
lines = file.split('\n')
sections = file.split('\n\n')
grid = [[char for char in row] for row in lines]


emptyColumns = []
emptyRows = []
galaxies = []

def prep():
    for row in range(len(grid)):
        isEmpty = True
        for column in range(len(grid[0])):
            if grid[row][column] == '#':
                isEmpty = False
                galaxies.append((row, column))
        if isEmpty:
            emptyRows.append(row)

    for column in range(len(grid[0])):
        isEmpty = True
        for row in range(len(grid)):
            if grid[row][column] == '#':
                isEmpty = False
                break
        if isEmpty:
            emptyColumns.append(column)

def part1():
    result = 0
    for firstIndex, (firstRow, firstColumn) in enumerate(galaxies):
        for secondIndex, (secondRow, secondColumn) in enumerate(galaxies):
            if firstIndex > secondIndex:
                continue

            distance = abs(firstRow - secondRow) + abs(firstColumn - secondColumn)

            for emptyRow in emptyRows:
                if min(firstRow, secondRow) <= emptyRow <= max(firstRow, secondRow):
                    distance += 1

            for emptyColumn in emptyColumns:
                if min(firstColumn, secondColumn) <= emptyColumn <= max(firstColumn, secondColumn):
                    distance += 1

            result += distance
    return result


def part2():
    emptyFactor = 10**6-1
    result = 0
    for firstIndex, (firstRow, firstColumn) in enumerate(galaxies):
        for secondIndex, (secondRow, secondColumn) in enumerate(galaxies):
            if firstIndex > secondIndex:
                continue

            distance = abs(firstRow - secondRow) + abs(firstColumn - secondColumn)

            for emptyRow in emptyRows:
                if min(firstRow, secondRow) <= emptyRow <= max(firstRow, secondRow):
                    distance += emptyFactor

            for emptyColumn in emptyColumns:
                if min(firstColumn, secondColumn) <= emptyColumn <= max(firstColumn, secondColumn):
                    distance += emptyFactor

            result += distance
    return result

print("Prepare")
print(round(timeit.timeit('prep()', globals=globals(), number=1) * 1000, 4), 'ms\n')
print("Part 1")
print(round(timeit.timeit('print(part1())', globals=globals(), number=1) * 1000, 4), 'ms\n')
print("Part 2")
print(round(timeit.timeit('print(part2())', globals=globals(), number=1) * 1000, 4), 'ms')