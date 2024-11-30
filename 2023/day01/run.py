def part1(file):
    lines = file.split('\n')

    result = 0
    for line in lines:
        firstIndex = 0
        while not line[firstIndex].isnumeric():
            firstIndex += 1

        lastIndex = len(line) - 1
        while not line[lastIndex].isnumeric():
            lastIndex -= 1

        firstNumber = line[firstIndex]
        lastNumber = line[lastIndex]

        innerResult = int(firstNumber + lastNumber)
        result += innerResult

    return result

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

def part2(file):
    lines = file.split('\n')

    result = 0
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

        innerResult = int(firstNumber + lastNumber)
        result += innerResult

    return result
