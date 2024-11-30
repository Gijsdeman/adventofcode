from collections import deque

# file = open('input').read().strip()
# lines = file.split('\n')
# sections = file.split('\n\n')
# grid = [['.' for c in row] for row in lines]
#
# workflows = {}

#
def prepare(sections, workflows):
    for line in sections[0].split('\n'):
        workflow, conditions = line.split('{')
        conditions = conditions.replace('}', '')
        conditions = conditions.split(',')
        parsedConditions = []
        for condition in conditions:
            if ':' in condition:
                expression, newWorkflow = condition.split(':')
                parsedConditions.append((expression[0], expression[1], int(expression[2:]), newWorkflow))
            else:
                parsedConditions.append((True, True, True, condition))
        workflows[workflow] = parsedConditions


def part1(file):
    workflows = {}
    sections = file.split('\n\n')
    prepare(sections, workflows)

    result = 0
    for line in sections[1].split('\n'):
        line = line.replace('{', '').replace('}', '')
        x, m, a, s = line.split(',')
        x, m, a, s = int(x[2:]), int(m[2:]), int(a[2:]), int(s[2:])
        xmas = {'x': x, 'm': m, 'a': a, 's': s}

        currentWorkflow = 'in'
        while True:
            if currentWorkflow == 'A' or currentWorkflow == 'R':
                break
            currentConditions = workflows[currentWorkflow]
            for category, inequality, value, newWorkflow in currentConditions:
                if category == inequality == value:
                    currentWorkflow = newWorkflow
                    break
                elif inequality == '<' and xmas[category] < value:
                    currentWorkflow = newWorkflow
                    break
                elif inequality == '>' and xmas[category] > value:
                    currentWorkflow = newWorkflow
                    break

        if currentWorkflow == 'A':
            result += x + m + a + s
    return result


def part2(file):
    workflows = {}
    sections = file.split('\n\n')
    prepare(sections, workflows)

    result = 0
    queue = deque()
    queue.append(('in', 0, {category: (1, 4000) for category in 'xmas'}))

    while len(queue) > 0:
        workflow, conditionalIndex, ranges = queue.popleft()

        if workflow == 'A' or workflow == 'R':
            if workflow == 'A':
                innerResult = 1
                for category in 'xmas':
                    # Every combination in the range that was accepted
                    innerResult *= ranges[category][1] - ranges[category][0] + 1
                result += innerResult
            continue

        category, inequality, value, newWorkflow = workflows[workflow][conditionalIndex]

        if category == inequality == value:
            queue.append((newWorkflow, 0, ranges))
        if inequality == '<':
            # Similar idea to day 5
            # map non-matching ranges to new workflow and continue to next mapping for others
            lowerRange = {**ranges, category: (ranges[category][0], value - 1)}
            upperRange = {**ranges, category: (value, ranges[category][1])}

            queue.append((newWorkflow, 0, lowerRange))
            queue.append((workflow, conditionalIndex + 1, upperRange))
        elif inequality == '>':
            # Similar idea to day 5
            # map non-matching ranges to new workflow and continue to next mapping for others
            lowerRange = {**ranges, category: (value + 1, ranges[category][1])}
            upperRange = {**ranges, category: (ranges[category][0], value)}

            queue.append((newWorkflow, 0, lowerRange))
            queue.append((workflow, conditionalIndex + 1, upperRange))
    return result