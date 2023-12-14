import timeit
import math

file = open('input', 'r').read().strip()
lines = file.split('\n')
grid = [[char for char in row] for row in lines]


def part1():
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


def part2():
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


print("Part 1")
print(round(timeit.timeit('print(part1())', globals=globals(), number=1) * 1000, 4), 'ms\n')
print("Part 2")
print(round(timeit.timeit('print(part2())', globals=globals(), number=1) * 1000, 4), 'ms')
