import timeit
from collections import deque
from math import lcm

file = open('input').read().strip()
lines = file.split('\n')
sections = file.split('\n\n')
grid = [['.' for c in row] for row in lines]

configuration = {}
lastInputs = {}
isConjunction = {}
currentState = {}


def prepare():
    for line in lines:
        startModule, targetModules = line.split(' -> ')
        currentStrip = startModule[1:]
        currentState[currentStrip] = False
        isConjunction[currentStrip] = True if startModule[0] == '&' else False
        configuration[currentStrip] = targetModules.split(', ')

    for startModule, targetModules in configuration.items():
        for targetModule in targetModules:
            if targetModule not in lastInputs:
                lastInputs[targetModule] = {}
            lastInputs[targetModule][startModule] = False


def part1():
    queue = deque()
    lowResult = 0
    highResult = 0

    for _ in range(0, 1000):
        buttonPress = configuration['roadcaster']
        # Button press
        lowResult += 1
        for targetModules in buttonPress:
            queue.append((targetModules, False))

        # Cycle until no more signals are send
        while len(queue) > 0:
            module, isHigh = queue.popleft()
            if isHigh:
                highResult += 1
            else:
                lowResult += 1

            # Happens when end module
            if module not in configuration:
                continue

            if not isConjunction[module] and not isHigh:
                # Update
                currentState[module] = not currentState[module]

                # Send signals, update conjunctions
                for targetModules in configuration[module]:
                    queue.append((targetModules, currentState[module]))
                    if isConjunction[targetModules]:
                        lastInputs[targetModules][module] = currentState[module]

            elif isConjunction[module]:
                # Update
                conjunction = True
                for _, inputModule in lastInputs[module].items():
                    conjunction = inputModule and conjunction
                currentState[module] = not conjunction

                # Send signals, update conjunctions
                for targetModules in configuration[module]:
                    queue.append((targetModules, currentState[module]))
                    if targetModules in configuration and isConjunction[targetModules]:
                        lastInputs[targetModules][module] = currentState[module]

    return highResult * lowResult


def part2():
    queue = deque()

    # Similar to day 8, we find cycle and calculate LCM
    # These must be low for rx to be high
    lowTargets = set(lastInputs[list(lastInputs['rx'].keys())[0]].keys())
    buttonPresses = 0
    visited = {}
    cycleLength = {}

    # Cycle until we have cycles for all four items
    while len(cycleLength) < len(lowTargets):
        buttonPress = configuration['roadcaster']
        # Button press
        buttonPresses += 1
        for targetModules in buttonPress:
            queue.append((targetModules, False))

        # Cycle until no more signals are send
        while len(queue) > 0:
            module, isHigh = queue.popleft()

            # Happens when end module
            if module not in configuration:
                continue

            # Check if low and if in targets
            if not isHigh and module in lowTargets:
                # If not visited, add current buttonpress to dictionary
                if module not in visited:
                    visited[module] = buttonPresses
                # If visited before, calculate presses it took to get here again
                elif module not in cycleLength:
                    cycleLength[module] = buttonPresses - visited[module]

            if not isConjunction[module] and not isHigh:
                # Update
                currentState[module] = not currentState[module]

                # Send signals, update conjunctions
                for targetModules in configuration[module]:
                    queue.append((targetModules, currentState[module]))
                    if isConjunction[targetModules]:
                        lastInputs[targetModules][module] = currentState[module]

            elif isConjunction[module]:
                # Update
                conjunction = True
                for _, inputModule in lastInputs[module].items():
                    conjunction = inputModule and conjunction
                currentState[module] = not conjunction

                # Send signals, update conjunctions
                for targetModules in configuration[module]:
                    queue.append((targetModules, currentState[module]))
                    if targetModules in configuration and isConjunction[targetModules]:
                        lastInputs[targetModules][module] = currentState[module]

    # Calculate LCM of the cycles
    result = lcm(*cycleLength.values())
    return result


print("Prepare")
print(round(timeit.timeit('prepare()', globals=globals(), number=1) * 1000, 4), 'ms\n')
print("Part 1")
print(round(timeit.timeit('print(part1())', globals=globals(), number=1) * 1000, 4), 'ms\n')
print("Part 2")
print(round(timeit.timeit('print(part2())', globals=globals(), number=1) * 1000, 4), 'ms')
