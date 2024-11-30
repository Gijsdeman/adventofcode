def part1(file):
    lines = file.split('\n')
    grid = [[char for char in row] for row in lines]
    width = len(grid[0])
    height = len(grid)
    newGrid = [['.' for _ in row] for row in lines]

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


def part2(file):
    lines = file.split('\n')
    grid = [[char for char in row] for row in lines]
    width = len(grid[0])
    height = len(grid)

    newGrid = [['.' for _ in row] for row in lines]
    visited = {}

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

    result = 0
    for row in range(height):
        for column in range(width):
            if grid[row][column] == 'O':
                result += height - row
    return result
