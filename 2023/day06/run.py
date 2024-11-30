import math

def part1(file):
    lines = file.split('\n')
    result = 1

    times = lines[0].split(":")[1].split()
    distances = lines[1].split(":")[1].split()

    for index in range(0, len(times)):
        innerResult = 0
        raceTime = times[index]
        record = distances[index]
        for timePressed in range(0, int(raceTime)):
            potentialRecord = timePressed * (int(raceTime) - timePressed)
            if potentialRecord > int(record):
                innerResult += 1
        result *= innerResult
    return result

def part2naive(file):
    lines = file.split('\n')
    result = 0

    time = ''.join(lines[0].split(":")[1].split())
    distance = ''.join(lines[1].split(":")[1].split())

    for timePressed in range(0, int(time)):
        potentialRecord = timePressed * (int(time) - timePressed)
        if potentialRecord > int(distance):
            result += 1
    return result

def part2derivative(file):
    lines = file.split('\n')

    time = int(''.join(lines[0].split(":")[1].split()))
    distance = int(''.join(lines[1].split(":")[1].split()))

    lower = math.floor(0.5 * (time - math.sqrt(time * time - 4 * distance)))
    upper = math.floor(0.5 * (time + math.sqrt(time * time - 4 * distance)))
    return upper - lower

def part2(file):
    return part2derivative(file)
    # return part2naive(file)
