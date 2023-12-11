import numpy as np
import time

startTime = time.perf_counter()

file = open('day11.input', 'r')
galaxyMap = file.readlines()
galaxyMap = [[char for char in row.replace('\n', '')] for row in galaxyMap]
galaxyMap = np.array(galaxyMap)

endTime = time.perf_counter()
elapsed = endTime - startTime

print("Read", round(elapsed, 4), "ms")

startTime = time.perf_counter()

emptyColumns = []
emptyRows = []
galaxies = []

for row in range(len(galaxyMap)):
    isEmpty = True
    for column in range(len(galaxyMap[0])):
        if galaxyMap[row][column] == '#':
            isEmpty = False
            galaxies.append((row, column))
    if isEmpty:
        emptyRows.append(row)

for column in range(len(galaxyMap[0])):
    isEmpty = True
    for row in range(len(galaxyMap)):
        if galaxyMap[row][column] == '#':
            isEmpty = False
            break
    if isEmpty:
        emptyColumns.append(column)

endTime = time.perf_counter()
elapsed = endTime - startTime

print("Prepare", round(elapsed, 4), "ms")
print("")

startTime = time.perf_counter()

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

endTime = time.perf_counter()
elapsed = endTime - startTime

print("Part 1")
print(result)
print(round(elapsed, 4), "ms")
print("")

startTime = time.perf_counter()

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

endTime = time.perf_counter()
elapsed = endTime - startTime

print("Part 2")
print(result)
print(round(elapsed, 4), "ms")
