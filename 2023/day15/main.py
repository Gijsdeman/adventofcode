import timeit
import math

file = open('input', 'r').read().strip()
lines = file.split(',')
sections = file.split('\n\n')
grid = [[char for char in row] for row in lines]


def hash(word):
    innerResult = 0
    for char in word:
        innerResult += ord(char)
        innerResult *= 17
        innerResult = innerResult % 256
    return innerResult


def part1():
    result = 0
    for line in lines:
        result += hash(line)
    return result


def part2():
    hashmap = {i: {} for i in range(0, 256)}

    for line in lines:
        if '=' in line:
            box, value = line.split('=')
            hashValue = hash(box)
            hashmap[hashValue][box] = value
        if '-' in line:
            box, _ = line.split('-')
            hashValue = hash(box)
            if box in hashmap[hashValue]:
                del hashmap[hashValue][box]

    result = 0
    for boxNumber, lensMap in hashmap.items():
        for lensIndex, lensValue in enumerate(lensMap.items()):
            result += (int(boxNumber) + 1) * (lensIndex + 1) * int(lensValue[1])

    return result


print("Part 1")
print(round(timeit.timeit('print(part1())', globals=globals(), number=1) * 1000, 4), 'ms\n')
print("Part 2")
print(round(timeit.timeit('print(part2())', globals=globals(), number=1) * 1000, 4), 'ms')
