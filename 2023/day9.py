file = open('day9.input', 'r')
lines = file.readlines()


def allZero(input):
    for item in input:
        if not int(item) == 0:
            return False
    return True


backward = 0
forward = 0

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

    innerBackward = 0
    for index in range(len(pascal) - 1, -1, -1):
        innerBackward = pascal[index][0] - innerBackward

    forward += innerForward
    backward += innerBackward

print("Part 1")
print(int(forward))
print("")
print("Part 2")
print(int(backward))
