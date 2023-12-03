file = open('day3.input', 'r')
lines = file.readlines()

result = 0

for line in lines:
    rucksackSize = int(len(line) / 2)
    firstSack = line[:rucksackSize]
    secondSack = line[rucksackSize:]

    matchChar = ''

    for first in firstSack:
        for second in secondSack:
            if first == second:
                matchChar = first

    if matchChar.isupper():
        # print(ord(matchChar) - 38)
        result += ord(matchChar) - 38
    else:
        # print(ord(matchChar) - 96)
        result += ord(matchChar) - 96

print("Part 1")
print(result)
print('')

result = 0
for index in range(0, len(lines), 3):
    firstSack = lines[index]
    secondSack = lines[index + 1]
    thirdSack = lines[index + 2]

    firstSackSet = set(firstSack)
    secondSackSet = set(secondSack)
    thirdSet = set(thirdSack)
    intersection = firstSackSet.intersection(secondSackSet).intersection(thirdSet)
    if '\n' in intersection:
        intersection.remove('\n')

    matchChar = intersection.pop()
    if matchChar.isupper():
        # print(ord(matchChar) - 38)
        result += ord(matchChar) - 38
    else:
        # print(ord(matchChar) - 96)
        result += ord(matchChar) - 96

print("Part 2")
print(result)