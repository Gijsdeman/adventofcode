import math

def part1(file):
    lines = file.split('\n')
    result = 0

    for line in lines:
        trash, stratches = line.split(': ')
        winning, own = map(lambda item: item.split(), stratches.split(' | '))

        power = -1
        for winningNumber in winning:
            if winningNumber in own:
                power += 1

        result += math.pow(2, power) if power >= 0 else 0

    return int(result)


def part2(file):
    lines = file.split('\n')
    result = 0
    copies = [0 for i in range(0, 300)]

    for line in lines:
        game, stratches = line.split(': ')

        copiesIndex = int(game.replace('Card ', ''))
        copies[copiesIndex] += 1

        winning, own = map(lambda item: item.split(), stratches.split(' | '))

        totalScore, pointer = 0, 1
        for winningNumber in winning:
            if winningNumber in own:
                copies[copiesIndex + pointer] += copies[copiesIndex]
                pointer += 1
        result += int(copies[copiesIndex])
    return result