def prep(file):
    lines = file.split('\n')
    grid = [[char for char in row] for row in lines]

    emptyColumns = []
    emptyRows = []
    galaxies = []

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

    return emptyColumns, emptyRows, galaxies

def part1(file):
    emptyColumns, emptyRows, galaxies = prep(file)

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


def part2(file):
    emptyColumns, emptyRows, galaxies = prep(file)

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
