import numpy as np
from collections import deque


def checkNext(firstTuple, width, height, grid):
    count = set()
    visited = set()
    queue = deque()

    queue.append(firstTuple)

    while len(queue) > 0:
        coordinate, direction = queue.popleft()
        if (coordinate, direction) in visited:
            continue
        visited.add((coordinate, direction))

        if 0 <= coordinate[0] < height and 0 <= coordinate[1] < width:
            count.add(coordinate)
            if grid[coordinate] == '-' and (direction == 2 or direction == 4):
                if direction == 2:
                    queue.append(((coordinate[0], coordinate[1] + 1), 2))
                else:
                    queue.append(((coordinate[0], coordinate[1] - 1), 4))
            elif grid[coordinate] == '-' and (direction == 1 or direction == 3):
                queue.append(((coordinate[0], coordinate[1] - 1), 4))
                queue.append(((coordinate[0], coordinate[1] + 1), 2))
            elif grid[coordinate] == '|' and (direction == 1 or direction == 3):
                if direction == 1:
                    queue.append(((coordinate[0] - 1, coordinate[1]), 1))
                else:
                    queue.append(((coordinate[0] + 1, coordinate[1]), 3))
            elif grid[coordinate] == '|' and (direction == 4 or direction == 2):
                queue.append(((coordinate[0] + 1, coordinate[1]), 3))
                queue.append(((coordinate[0] - 1, coordinate[1]), 1))
            elif grid[coordinate] == '/':
                if direction == 2:
                    queue.append(((coordinate[0] - 1, coordinate[1]), 1))
                elif direction == 3:
                    queue.append(((coordinate[0], coordinate[1] - 1), 4))
                elif direction == 1:
                    queue.append(((coordinate[0], coordinate[1] + 1), 2))
                else:
                    queue.append(((coordinate[0] + 1, coordinate[1]), 3))
            elif grid[coordinate] == '\\':
                if direction == 2:
                    queue.append(((coordinate[0] + 1, coordinate[1]), 3))
                elif direction == 3:
                    queue.append(((coordinate[0], coordinate[1] + 1), 2))
                elif direction == 1:
                    queue.append(((coordinate[0], coordinate[1] - 1), 4))
                else:
                    queue.append(((coordinate[0] - 1, coordinate[1]), 1))
            else:
                if direction == 2:
                    queue.append(((coordinate[0], coordinate[1] + 1), 2))
                elif direction == 4:
                    queue.append(((coordinate[0], coordinate[1] - 1), 4))
                elif direction == 1:
                    queue.append(((coordinate[0] - 1, coordinate[1]), 1))
                else:
                    queue.append(((coordinate[0] + 1, coordinate[1]), 3))
    return len(count)


def part1(file):
    lines = file.split('\n')
    grid = [[char for char in row] for row in lines]
    grid = np.array(grid)

    height = len(grid)
    width = len(grid[0])

    return checkNext(((0, 0), 2), width, height, grid)


def part2(file):
    lines = file.split('\n')
    grid = [[char for char in row] for row in lines]
    grid = np.array(grid)

    height = len(grid)
    width = len(grid[0])

    result = 0
    for column in range(0, width):
        result = max(result, checkNext(((0, column), 3), width, height, grid))

    for column in range(0, width):
        result = max(result, checkNext(((height - 1, column), 1), width, height, grid))

    for row in range(0, height):
        result = max(result, checkNext(((row, 0), 2), width, height, grid))

    for row in range(0, height):
        result = max(result, checkNext(((width - 1, row), 4), width, height, grid))

    return result