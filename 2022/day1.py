file = open('day1.input', 'r')
lines = file.readlines()

currentCals = 0
maxCals = 0
allCals = []

for calories in lines:
    if calories == '\n':
        maxCals = max(currentCals, maxCals)
        allCals.append(int(currentCals))
        currentCals = 0
    else:
        currentCals += int(calories)

allCals.sort(reverse=True)
print(allCals[0] + allCals[1] + allCals[2])
print(maxCals)