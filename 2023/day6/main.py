import timeit
import math

file = open('input', 'r').read().strip()
lines = file.split('\n')
sections = file.split('\n\n')
grid = [[char for char in row] for row in lines]


def part1():
    result = 1

    times = lines[0].split(":")[1].split()
    distances = lines[1].split(":")[1].split()

    for index in range(0, len(times)):
        innerResult = 0;
        raceTime = times[index]
        record = distances[index]
        for timePressed in range(0, int(raceTime)):
            potentialRecord = timePressed * (int(raceTime) - timePressed)
            if potentialRecord > int(record):
                innerResult += 1
        result *= innerResult
    return result


def part2():
    result = 0

    time = ''.join(lines[0].split(":")[1].split())
    distance = ''.join(lines[1].split(":")[1].split())

    for timePressed in range(0, int(time)):
        potentialRecord = timePressed * (int(time) - timePressed)
        if potentialRecord > int(distance):
            result += 1
    return result


def part2derivative():
    time = int(''.join(lines[0].split(":")[1].split()))
    distance = int(''.join(lines[1].split(":")[1].split()))

    lower = math.floor(0.5 * (time - math.sqrt(time * time - 4 * distance)))
    upper = math.floor(0.5 * (time + math.sqrt(time * time - 4 * distance)))
    return upper - lower


print("Part 1")
print(round(timeit.timeit('print(part1())', globals=globals(), number=1) * 1000, 4), 'ms\n')
print("Part 2")
print(round(timeit.timeit('print(part2())', globals=globals(), number=1) * 1000, 4), 'ms\n')
print("Part 2 - Derivative")
print(round(timeit.timeit('print(part2derivative())', globals=globals(), number=1) * 1000, 4), 'ms')