import timeit
import numpy as np
from queue import PriorityQueue
import math

file = open('input').read().strip()
lines = file.split('\n')
grid = [[int(c) for c in row] for row in lines]
grid = np.array(grid)

rows = len(grid)
columns = len(grid[0])

getPosition = [
    lambda xy: (xy[0], xy[1] - 1),
    lambda xy: (xy[0] - 1, xy[1]),
    lambda xy: (xy[0], xy[1] + 1),
    lambda xy: (xy[0] + 1, xy[1])
]


def part1():
    queue = PriorityQueue()
    queue.put((0, ((0, 0), -1, -1)))
    visited = {}

    while not queue.empty():
        distance, (currentPosition, currentDirection, consecutive) = queue.get()

        if (currentPosition, currentDirection, consecutive) in visited:
            continue
        visited[(currentPosition, currentDirection, consecutive)] = distance

        for newDirection in range(4):
            newConsecutive = 1 if newDirection != currentDirection else consecutive + 1

            if newConsecutive > 3:
                continue

            if (newDirection + 2) % 4 == currentDirection:
                continue

            newPosition = getPosition[newDirection](currentPosition)

            if 0 <= newPosition[0] < rows and 0 <= newPosition[1] < columns:
                queue.put((distance + int(grid[newPosition]), (newPosition, newDirection, newConsecutive)))

    result = math.inf
    for (position, _, _), distance in visited.items():
        if position == (rows - 1, columns - 1):
            result = min(result, distance)
    return result


def part2():
    queue = PriorityQueue()
    queue.put((0, ((0, 0), -1, -1)))
    visited = {}

    while not queue.empty():
        distance, (currentPosition, currentDirection, consecutive) = queue.get()

        if (currentPosition, currentDirection, consecutive) in visited:
            continue
        visited[(currentPosition, currentDirection, consecutive)] = distance

        for newDirection in range(4):
            newConsecutive = 1 if newDirection != currentDirection else consecutive + 1

            if (newConsecutive > 10) or (newDirection != currentDirection and 0 <= consecutive < 4):
                continue

            if (newDirection + 2) % 4 == currentDirection:
                continue

            newPosition = getPosition[newDirection](currentPosition)

            if 0 <= newPosition[0] < rows and 0 <= newPosition[1] < columns:
                queue.put((distance + int(grid[newPosition]), (newPosition, newDirection, newConsecutive)))

    result = math.inf
    for (position, _, _), distance in visited.items():
        if position == (rows - 1, columns - 1):
            result = min(result, distance)
    return result


print("Part 1")
print(round(timeit.timeit('print(part1())', globals=globals(), number=1) * 1000, 4), 'ms\n')
print("Part 2")
print(round(timeit.timeit('print(part2())', globals=globals(), number=1) * 1000, 4), 'ms')
