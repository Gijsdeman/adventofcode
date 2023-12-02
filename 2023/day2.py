file = open('day2.input', 'r')
lines = file.readlines()
import re

colors = {
    'red': 12,
    'green': 13,
    'blue': 14
}

count = 0
result = 0

for line in lines:
    splitLine = line.split(':')
    gameId = re.search(r'\d+', splitLine[0])

    games = splitLine[1].split('; ')
    goodGame = True
    for color in colors:
        colors[color] = -1

    for set in games:
        cubes = set.split(', ')
        for cube in cubes:
            for color in colors:
                if color in cube:
                    cube = cube.replace(' ' + color, '')
                    if int(cube) > colors[color]:
                        # For challenge 1
                        goodGame = False
                        # For challenge 2
                        colors[color] = int(cube)

    innerResult = 1
    for color in colors:
        innerResult *= colors[color]

    # for challenge 1
    # if goodGame:
    result += innerResult

print(result)