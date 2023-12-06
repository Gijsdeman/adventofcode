file = open('day1.input', 'r')
lines = file.readlines()

numbers = {
    'zero': '0',
    'one': '1',
    'two': '2',
    'three': '3',
    'four': '4',
    'five': '5',
    'six': '6',
    'seven': '7',
    'eight': '8',
    'nine': '9'
}

count = 0
for line in lines:

    firstIndex = 0
    while not line[firstIndex].isnumeric() and firstIndex < len(line) - 1:
        firstIndex += 1

    lastIndex = len(line) - 1
    while not line[lastIndex].isnumeric() and lastIndex >= 0:
        lastIndex -= 1

    firstNumber = line[firstIndex]
    lastNumber = line[lastIndex]

    for written in numbers.keys():
        randomFirstIndex = line.find(written)
        if randomFirstIndex < firstIndex and randomFirstIndex != -1:
            firstIndex = randomFirstIndex
            firstNumber = numbers[written]

        randomLastIndex = line.rfind(written)
        if randomLastIndex > lastIndex:
            lastIndex = randomLastIndex
            lastNumber = numbers[written]

    result = int(firstNumber + lastNumber)
    count += result

print(count)
