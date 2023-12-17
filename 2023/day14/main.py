import timeit

file = open('input', 'r').read().strip()
lines = file.split('\n')
grid = [[char for char in row] for row in lines]

width = len(grid[0])
height = len(grid)

newGrid = [['.' for _ in row] for row in lines]
startGrid = grid
visited = {}


def part1():
    for column in range(width):
        rollRow = 0
        for row in range(height):
            if grid[row][column] == 'O':
                newGrid[rollRow][column] = 'O'
                rollRow = rollRow + 1
            if row < height and grid[row][column] == '#':
                newGrid[row][column] = '#'
                rollRow = row + 1

    result = 0
    for row in range(height):
        for column in range(width):
            if newGrid[row][column] == 'O':
                result += height - row
    return result


def part2():
    global grid, newGrid, startGrid

    totalCycles, currentCycle = 10**9, 0
    while currentCycle < totalCycles:
        currentCycle += 1

        # Roll north
        for column in range(width):
            rollRow = 0
            for row in range(height):
                if grid[row][column] == 'O':
                    newGrid[rollRow][column] = 'O'
                    rollRow = rollRow + 1
                if row < height and grid[row][column] == '#':
                    newGrid[row][column] = '#'
                    rollRow = row + 1
        grid = newGrid
        newGrid = [['.' for _ in row] for row in lines]

        # Roll west
        for row in range(height):
            rollColumn = 0
            for column in range(width):
                if grid[row][column] == 'O':
                    newGrid[row][rollColumn] = 'O'
                    rollColumn = rollColumn + 1
                if row < height and grid[row][column] == '#':
                    newGrid[row][column] = '#'
                    rollColumn = column + 1

        grid = newGrid
        newGrid = [['.' for _ in row] for row in lines]

        # Roll south
        for column in range(width):
            rollRow = width - 1
            for row in range(height - 1, -1, -1):
                if grid[row][column] == 'O':
                    newGrid[rollRow][column] = 'O'
                    rollRow = rollRow - 1
                if row < height and grid[row][column] == '#':
                    newGrid[row][column] = '#'
                    rollRow = row - 1
        grid = newGrid
        newGrid = [['.' for _ in row] for row in lines]

        # Roll east
        for row in range(height):
            rollColumn = height - 1
            for column in range(width - 1, -1, -1):
                if grid[row][column] == 'O':
                    newGrid[row][rollColumn] = 'O'
                    rollColumn = rollColumn - 1
                if row < height and grid[row][column] == '#':
                    newGrid[row][column] = '#'
                    rollColumn = column - 1
        grid = newGrid
        newGrid = [['.' for _ in row] for row in lines]

        if str(grid) in visited:
            cycleLength = currentCycle - visited[str(grid)]
            factor = (totalCycles - currentCycle) // cycleLength
            currentCycle += factor * cycleLength
        visited[str(grid)] = currentCycle
        startGrid = grid

    result = 0
    for row in range(height):
        for column in range(width):
            if grid[row][column] == 'O':
                result += height - row
    return result


print("Part 1")
print(round(timeit.timeit('print(part1())', globals=globals(), number=1) * 1000, 4), 'ms\n')
print("Part 2")
print(round(timeit.timeit('print(part2())', globals=globals(), number=1) * 1000, 4), 'ms')
