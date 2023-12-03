file = open('day4.input', 'r')
lines = file.readlines()

result = 0
for line in lines:
    sections = line.replace('\n','').split(',')
    firstSections = sections[0].split('-')
    secondSections = sections[1].split('-')

    if int(firstSections[0]) <= int(secondSections[0]) and int(firstSections[1]) >= int(secondSections[1]):
        result += 1
    elif int(secondSections[0]) <= int(firstSections[0]) and int(secondSections[1]) >= int(firstSections[1]):
        result += 1

print("First part:")
print(result)
print('')

result = 0
for line in lines:
    sections = line.replace('\n','').split(',')
    firstSections = sections[0].split('-')
    secondSections = sections[1].split('-')

    if int(secondSections[0]) <= int(firstSections[0]) <= int(secondSections[1]) or int(secondSections[0]) <= int(firstSections[1]) <= int(secondSections[1]):
        result += 1
    elif int(firstSections[0]) <= int(secondSections[0]) <= int(firstSections[1]) or int(firstSections[0]) <= int(secondSections[1]) <= int(firstSections[1]):
        result += 1

print("Second part:")
print(result)
