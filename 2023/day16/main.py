import timeit
import numpy as np
from collections import deque

file = open('input', 'r').read().strip()
lines = file.split('\n')
sections = file.split('\n\n')
grid = [[char for char in row] for row in lines]
grid = np.array(grid)

height = len(grid)
width = len(grid[0])

count = set()
visited = set()
queue = deque()


def checkNext(firstTuple):
    queue.clear()
    queue.append(firstTuple)

    visited.clear()
    count.clear()

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


def part1():
    return checkNext(((0, 0), 2))


def part2():
    result = 0
    for column in range(0, width):
        result = max(result, checkNext(((0, column), 3)))

    for column in range(0, width):
        result = max(result, checkNext(((height - 1, column), 1)))

    for row in range(0, height):
        result = max(result, checkNext(((row, 0), 2)))

    for row in range(0, height):
        result = max(result, checkNext(((width - 1, row), 4)))

    return result


print("Part 1")
print(round(timeit.timeit('print(part1())', globals=globals(), number=1) * 1000, 4), 'ms\n')
print("Part 2")
print(round(timeit.timeit('print(part2())', globals=globals(), number=1) * 1000, 4), 'ms')
