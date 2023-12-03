import copy
import re

file = open('day5.input', 'r')
lines = file.readlines()

index = 0
startLine = 0
maxBucket = 0

# Reading all the input
while True:
    if lines[index] == '\n':
        startLine = index
        maxBucket = int(lines[index - 1][len(lines[index - 1]) - 2])
        break
    else:
        index += 1

stacks = [[] for i in range(0, maxBucket)]

for index in range(startLine - 2, -1, -1):
    for item in range(0, maxBucket):
        if item * 4 + 1 >= len(lines[index]):
            break
        if lines[index][item * 4 + 1] == ' ':
            continue
        stacks[item].append(lines[index][item * 4 + 1])

stacksBac = copy.deepcopy(stacks)

# Actual start
for index in range(startLine + 1, len(lines)):
    line = lines[index].replace('move ', '').replace('from ', '').replace('to ', '')
    amounts = line.split()

    for move in range(0, int(amounts[0])):
        stacks[int(amounts[2]) - 1].append(stacks[int(amounts[1]) - 1].pop())

result = ''
for index in range(0, maxBucket):
    result += stacks[index].pop()

print("Part 1")
print(result)

stacks = stacksBac
for index in range(startLine + 1, len(lines)):
    line = lines[index].replace('move ', '').replace('from ', '').replace('to ', '')
    amounts = line.split()

    movedIndex = int(amounts[1])
    movedItems = stacks[int(amounts[1]) - 1][-int(amounts[0]):]
    for move in range(0, int(amounts[0])):
        stacks[int(amounts[1]) - 1].pop()
    stacks[int(amounts[2]) - 1] += movedItems

result = ''
for index in range(0, maxBucket):
    result += stacks[index].pop()

print("Part 2")
print(result)