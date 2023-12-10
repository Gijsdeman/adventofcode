from collections import deque
import time
import numpy as np


startTime = time.perf_counter()

file = open('day10.input', 'r')
pipeGrid = file.readlines()
pipeGrid = [[char for char in row.replace('\n', '')] for row in pipeGrid]
pipeGrid = np.array(pipeGrid)

endTime = time.perf_counter()
elapsed = endTime - startTime

print("Read", round(elapsed, 4), "ms")
print("")

startTime = time.perf_counter()

result = 0
start = (0, 0)

rows = len(pipeGrid)
columns = len(pipeGrid[0])

for lineIndex, line in enumerate(pipeGrid):
    for charIndex, char in enumerate(line):
        if char == 'S':
            start = (lineIndex, charIndex)

topPos = lambda xy: (xy[0] - 1, xy[1])
bottomPos = lambda xy: (xy[0] + 1, xy[1])
leftPos = lambda xy: (xy[0], xy[1] - 1)
rightPos = lambda xy: (xy[0], xy[1] + 1)

topChars = '|7F'
bottomChars = '|JL'
leftChars = '-FL'
rightChars = '-J7'

top = pipeGrid[topPos(start)] in topChars
bottom = pipeGrid[bottomPos(start)] in bottomChars
left = pipeGrid[leftPos(start)] in leftChars
right = pipeGrid[rightPos(start)] in rightChars

uncheckedPipes = deque()

if left and right:
    pipeGrid[start[0]][start[1]] = '-'
    uncheckedPipes.append((rightPos(start), start))
elif top and bottom:
    pipeGrid[start[0]][start[1]] = '|'
    uncheckedPipes.append((topPos(start), start))
elif bottom and right:
    pipeGrid[start[0]][start[1]] = 'F'
    uncheckedPipes.append((rightPos(start), start))
elif bottom and left:
    pipeGrid[start[0]][start[1]] = '7'
    uncheckedPipes.append((bottomPos(start), start))
elif top and right:
    pipeGrid[start[0]][start[1]] = 'L'
    uncheckedPipes.append((rightPos(start), start))
elif top and left:
    pipeGrid[start[0]][start[1]] = 'J'
    uncheckedPipes.append((topPos(start), start))

pipeCycle = set()

result = 0
while True:
    currentTuple = uncheckedPipes.popleft()
    currentPipe = currentTuple[0]
    previousPipe = currentTuple[1]
    pipeCycle.add(currentPipe)
    result += 1

    if currentPipe == start:
        break

    if pipeGrid[currentPipe] == '-':
        if currentPipe[1] > previousPipe[1]:
            uncheckedPipes.append((rightPos(currentPipe), currentPipe))
        else:
            uncheckedPipes.append((leftPos(currentPipe), currentPipe))

    elif pipeGrid[currentPipe] == '|':
        if currentPipe[0] > previousPipe[0]:
            uncheckedPipes.append((bottomPos(currentPipe), currentPipe))
        else:
            uncheckedPipes.append((topPos(currentPipe), currentPipe))

    elif pipeGrid[currentPipe] == 'F':
        if currentPipe[0] < previousPipe[0]:
            uncheckedPipes.append((rightPos(currentPipe), currentPipe))
        else:
            uncheckedPipes.append((bottomPos(currentPipe), currentPipe))

    elif pipeGrid[currentPipe] == '7':
        if currentPipe[0] < previousPipe[0]:
            uncheckedPipes.append((leftPos(currentPipe), currentPipe))
        else:
            uncheckedPipes.append((bottomPos(currentPipe), currentPipe))

    elif pipeGrid[currentPipe] == 'L':
        if currentPipe[0] > previousPipe[0]:
            uncheckedPipes.append((rightPos(currentPipe), currentPipe))
        else:
            uncheckedPipes.append((topPos(currentPipe), currentPipe))

    elif pipeGrid[currentPipe] == 'J':
        if currentPipe[0] > previousPipe[0]:
            uncheckedPipes.append((leftPos(currentPipe), currentPipe))
        else:
            uncheckedPipes.append((topPos(currentPipe), currentPipe))

endTime = time.perf_counter()
elapsed = endTime - startTime

print("Part 1")
print(int(result / 2))
print(round(elapsed, 4), "ms")
print("")

startTime = time.perf_counter()

newPipeGrid = [['.' for _ in range(columns * 3)] for _ in range(rows * 3)]
newPipeGrid = np.array(newPipeGrid)
newPipeCycle = set()


newPos = lambda xy: (xy[0] * 3 + 1, xy[1] * 3 + 1)
newTopPos = lambda xy: (xy[0] * 3, xy[1] * 3 + 1)
newBottomPos = lambda xy: (xy[0] * 3 + 2, xy[1] * 3 + 1)
newLeftPos = lambda xy: (xy[0] * 3 + 1, xy[1] * 3)
newRightPos = lambda xy: (xy[0] * 3 + 1, xy[1] * 3 + 2)


def makePipe(pipeLocation):
    newPipeGrid[pipeLocation] = 'x'
    newPipeCycle.add(pipeLocation)


for pipeLocation in pipeCycle:
    pipe = pipeGrid[pipeLocation]
    if pipe == '|':
        makePipe(newPos(pipeLocation))
        makePipe(newTopPos(pipeLocation))
        makePipe(newBottomPos(pipeLocation))
    if pipe == '-':
        makePipe(newPos(pipeLocation))
        makePipe(newLeftPos(pipeLocation))
        makePipe(newRightPos(pipeLocation))
    if pipe == 'F':
        makePipe(newPos(pipeLocation))
        makePipe(newRightPos(pipeLocation))
        makePipe(newBottomPos(pipeLocation))
    if pipe == '7':
        makePipe(newPos(pipeLocation))
        makePipe(newBottomPos(pipeLocation))
        makePipe(newLeftPos(pipeLocation))
    if pipe == 'L':
        makePipe(newPos(pipeLocation))
        makePipe(newRightPos(pipeLocation))
        makePipe(newTopPos(pipeLocation))
    if pipe == 'J':
        makePipe(newPos(pipeLocation))
        makePipe(newLeftPos(pipeLocation))
        makePipe(newTopPos(pipeLocation))

queue = deque()
visited = set()
queue.append((0, 0))

while len(queue) > 0:
    pipe = queue.popleft()
    for neighbourPipe in [topPos(pipe), bottomPos(pipe), leftPos(pipe), rightPos(pipe)]:
        if 0 <= neighbourPipe[0] < rows * 3 and 0 <= neighbourPipe[1] < columns * 3:
            if neighbourPipe in visited:
                continue
            if newPipeGrid[neighbourPipe] != 'x' and neighbourPipe not in visited:
                visited.add(neighbourPipe)
                queue.append(neighbourPipe)

result = 0
for row in range(rows):
    for column in range(columns):
        newVisited = False
        for bigRow in range(0, 3):
            for bigColumn in range(0, 3):
                if (3 * row + bigRow, 3 * column + bigColumn) in visited:
                    newVisited = True
        if newVisited:
            result += 1

endTime = time.perf_counter()
elapsed = endTime - startTime

print("Part 2")
print(rows * columns - result)
print(round(elapsed, 4), "ms")
print("")

startTime = time.perf_counter()

newPipeGrid = [['.' for _ in range(columns)] for _ in range(rows)]
newPipeGrid = np.array(newPipeGrid)
for pipe in pipeCycle:
    newPipeGrid[pipe] = pipeGrid[pipe]

result = 0
previousPipe = ''
for row in range(rows):
    parity = 0
    turning = False
    for column in range(columns):
        if newPipeGrid[row][column] != '.':
            currentPipe = newPipeGrid[row][column]

            if currentPipe == '|':
                parity += 1
                continue

            elif currentPipe == '-':
                continue

            if not turning:
                turning = True
                previousPipe = currentPipe

            else:
                if not (previousPipe == 'F' and currentPipe == '7') and not (previousPipe == 'L' and currentPipe == 'J'):
                    parity += 1
                turning = False

        elif parity % 2 == 1:
            result += 1

endTime = time.perf_counter()
elapsed = endTime - startTime

print("Part 2 - Parity")
print(result)
print(round(elapsed, 4), "ms")
