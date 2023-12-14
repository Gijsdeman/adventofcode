import timeit

file = open('input', 'r').read().strip()
lines = file.split('\n')
grid = [[char for char in row] for row in lines]

colors = {
    'red': 12,
    'green': 13,
    'blue': 14
}


def part1():
    result = 0
    for index, line in enumerate(lines):
        splitLine = line.split(':')
        games = splitLine[1].split('; ')
        goodGame = True

        for set in games:
            cubes = set.split(', ')
            for cube in cubes:
                for color in colors:
                    if color in cube:
                        cube = cube.replace(' ' + color, '')
                        if int(cube) > colors[color]:
                            goodGame = False

        if goodGame:
            result += index + 1

    return result


def part2():
    result = 0
    for line in lines:
        splitLine = line.split(':')
        games = splitLine[1].split('; ')
        for color in colors:
            colors[color] = -1

        for set in games:
            cubes = set.split(', ')
            for cube in cubes:
                for color in colors:
                    if color in cube:
                        cube = cube.replace(' ' + color, '')
                        if int(cube) > colors[color]:
                            colors[color] = int(cube)

        innerResult = 1
        for color in colors:
            innerResult *= colors[color]

        result += innerResult
    return result


print("Part 1")
print(round(timeit.timeit('print(part1())', globals=globals(), number=1) * 1000, 4), 'ms\n')
print("Part 2")
print(round(timeit.timeit('print(part2())', globals=globals(), number=1) * 1000, 4), 'ms')
