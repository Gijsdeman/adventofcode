import timeit

file = open('input', 'r').read().strip()
lines = file.split('\n')
sections = file.split('\n\n')
grid = [[char for char in row] for row in lines]


def allZero(input):
    for item in input:
        if not int(item) == 0:
            return False
    return True


def part1():
    result = 0
    for line in lines:
        values = line.split()
        newValues = values
        pascal = [list(map(lambda x: int(x), values))]
        while not allZero(newValues):
            oldValues = newValues
            newValues = []
            for index in range(1, len(oldValues)):
                newValues.append(int(oldValues[index]) - int(oldValues[index - 1]))
            pascal.append(newValues)

        innerForward = 0
        for index in range(len(pascal) - 1, -1, -1):
            innerForward += pascal[index][-1]

        result += innerForward
    return result


def part2():
    result = 0
    for line in lines:
        values = line.split()
        newValues = values
        pascal = [list(map(lambda x: int(x), values))]
        while not allZero(newValues):
            oldValues = newValues
            newValues = []
            for index in range(1, len(oldValues)):
                newValues.append(int(oldValues[index]) - int(oldValues[index - 1]))
            pascal.append(newValues)

        innerBackward = 0
        for index in range(len(pascal) - 1, -1, -1):
            innerBackward = pascal[index][0] - innerBackward

        result += innerBackward
    return result


print("Part 1")
print(round(timeit.timeit('print(part1())', globals=globals(), number=1) * 1000, 4), 'ms\n')
print("Part 2")
print(round(timeit.timeit('print(part2())', globals=globals(), number=1) * 1000, 4), 'ms')
