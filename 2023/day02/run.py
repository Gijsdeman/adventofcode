colors = {
    'red': 12,
    'green': 13,
    'blue': 14
}

def part1(file):
    lines = file.split('\n')

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

def part2(file):
    lines = file.split('\n')

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