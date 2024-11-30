import numpy as np

def part1slow(file):
    lines = file.split('\n')

    current = (0, 0)
    cycle = []

    for line in lines:
        direction, length, _ = line.split()

        for i in range(1, int(length) + 1):
            if direction == 'R':
                cycle.append((current[0], current[1] + i))
            elif direction == 'L':
                cycle.append((current[0], current[1] - i))
            elif direction == 'U':
                cycle.append((current[0] - i, current[1]))
            elif direction == 'D':
                cycle.append((current[0] + i, current[1]))

        current = cycle[-1]

    clockWise, counterClockWise = 0, 0
    for cycleIndex, current in enumerate(cycle):
        clockWise += current[0] * cycle[(cycleIndex + 1) % len(cycle)][1]
        counterClockWise += current[1] * cycle[(cycleIndex + 1) % len(cycle)][0]

    # In this instance points are considered "centered", i.e. we miscount half of the border length + 1
    return abs(clockWise - counterClockWise) / 2 + len(cycle) / 2 + 1


def part1optimised(file):
    lines = file.split('\n')

    current = (0, 0)
    polygon = []
    cycleLength = 0

    for line in lines:
        direction, length, _ = line.split()
        length = int(length)

        # Shoelace actually only needs the defining points of a polygon
        if direction == 'R':
            polygon.append((current[0], current[1] + length))
        elif direction == 'L':
            polygon.append((current[0], current[1] - length))
        elif direction == 'U':
            polygon.append((current[0] - length, current[1]))
        elif direction == 'D':
            polygon.append((current[0] + length, current[1]))
        cycleLength += length
        current = polygon[-1]

    clockWise, counterClockWise = 0, 0
    for cycleIndex, current in enumerate(polygon):
        clockWise += current[0] * polygon[(cycleIndex + 1) % len(polygon)][1]
        counterClockWise += current[1] * polygon[(cycleIndex + 1) % len(polygon)][0]

    # In this instance points are considered "centered", i.e. we miscount half of the border length + 1
    return abs(clockWise - counterClockWise) / 2 + cycleLength / 2 + 1

def part1(file):
    return part1optimised(file)
    # return part1slow(file)

def part2(file):
    lines = file.split('\n')

    current = (0, 0)
    polygon = []
    cycleLength = 0

    # Shoelace actually only needs the defining points of a polygon
    for line in lines:
        _, _, RGB = line.split()
        RGB = RGB.replace('(#', '').replace(')', '')
        length = int(RGB[:5], 16)
        test = ['R', 'D', 'L', 'U']
        direction = test[int(RGB[5:])]

        if direction == 'R':
            polygon.append((current[0], current[1] + length))
        elif direction == 'L':
            polygon.append((current[0], current[1] - length))
        elif direction == 'U':
            polygon.append((current[0] - length, current[1]))
        elif direction == 'D':
            polygon.append((current[0] + length, current[1]))
        cycleLength += length
        current = polygon[-1]

    clockWise, counterClockWise = 0, 0
    for cycleIndex, current in enumerate(polygon):
        clockWise += current[0] * polygon[(cycleIndex + 1) % len(polygon)][1]
        counterClockWise += current[1] * polygon[(cycleIndex + 1) % len(polygon)][0]

    # In this instance points are considered "centered", i.e. we miscount half of the border length + 1
    return abs(clockWise - counterClockWise) / 2 + cycleLength / 2 + 1
