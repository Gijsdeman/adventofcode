file = open('day8.input', 'r')
lines = file.readlines()
from math import gcd

result = 0
mapping = {}
instruction = lines[0]

for line in lines[2:]:
    location, tuple = line.split(" = ")
    tuple = tuple.replace("(", "").replace(")", "").replace("\n", "")
    tuple = tuple.split(", ")
    mapping[location] = tuple

current = 'AAA'
directionIndex = 0
while current != 'ZZZ':
    currentTuple = mapping[current]
    current = currentTuple[0 if instruction[directionIndex] == 'L' else 1]
    directionIndex += 1
    directionIndex %= len(instruction) - 1
    result += 1

print("Part 1")
print(int(result))
print("")

currentList = []
for key in mapping.keys():
    if key[-1] == 'A':
        currentList.append(key)


def checkEnds(locationList):
    for key in locationList:
        if key[-1] != 'Z':
            return False
    return True


results = []
for (startIndex, start) in enumerate(currentList):
    results.append(0)
    current = start
    directionIndex = 0
    while current[-1] != 'Z':
        currentTuple = mapping[current]
        current = currentTuple[0 if instruction[directionIndex] == 'L' else 1]
        directionIndex += 1
        directionIndex %= len(instruction) - 1
        results[startIndex] += 1

# Calculate least common multiple
result = 1
for item in results:
    result = result * item // gcd(result, item)

print("Part 2")
print(result)
