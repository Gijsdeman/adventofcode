import timeit

file = open('input', 'r').read().strip()
lines = file.split('\n')
sections = file.split('\n\n')
grid = [[char for char in row] for row in lines]


def sortPart1(hand):
    hand = hand.replace('J', chr(ord('9') + 2))

    charCount = {}
    for card in hand:
        charCount[card] = hand.count(card)

    sortedCounts = {key: value for key, value in
                    sorted(charCount.items(), key=lambda charTuple: -charTuple[1])}
    sortedCountsKeys = list(sortedCounts.keys())

    if sortedCounts[sortedCountsKeys[0]] == 5:
        return 7, hand
    elif sortedCounts[sortedCountsKeys[0]] == 4:
        return 6, hand
    elif sortedCounts[sortedCountsKeys[0]] == 3 and len(sortedCounts) > 1 and sortedCounts[sortedCountsKeys[1]] == 2:
        return 5, hand
    elif sortedCounts[sortedCountsKeys[0]] == 3:
        return 4, hand
    elif sortedCounts[sortedCountsKeys[0]] == 2 and len(sortedCounts) > 1 and sortedCounts[sortedCountsKeys[1]] == 2:
        return 3, hand
    elif sortedCounts[sortedCountsKeys[0]] == 2:
        return 2, hand
    else:
        return 1, hand


hands = []


def part1():
    for line in lines:
        hand, bid = line.split()
        hand = (hand
                .replace('T', chr(ord('9') + 1))
                .replace('Q', chr(ord('9') + 3))
                .replace('K', chr(ord('9') + 4))
                .replace('A', chr(ord('9') + 5)))
        hands.append((hand, bid))

    sortedHands = sorted(hands, key=lambda handTuple: sortPart1(handTuple[0]))

    result = 0
    for handIndex, hand in enumerate(sortedHands):
        result += (handIndex + 1) * int(hand[1])
    return result


def sortPart2(hand):
    hand = hand.replace('J', '1')

    charCount = {}
    for card in hand:
        charCount[card] = hand.count(card)

    sortedCounts = {key: value for key, value in
                    sorted(charCount.items(), key=lambda charTuple: -charTuple[1])}
    sortedCountsKeys = list(sortedCounts.keys())

    # Check if not all items are jokers
    if not (sortedCountsKeys[0] == '1' and len(sortedCountsKeys) == 1) and '1' in sortedCountsKeys:
        # If first item is joker increase second item
        if sortedCountsKeys[0] != '1':
            sortedCounts[sortedCountsKeys[0]] += sortedCounts['1']
        else:
            sortedCounts[sortedCountsKeys[1]] += sortedCounts['1']
        del sortedCounts['1']
        sortedCountsKeys = list(sortedCounts.keys())

    if sortedCounts[sortedCountsKeys[0]] == 5:
        return 7, hand
    elif sortedCounts[sortedCountsKeys[0]] == 4:
        return 6, hand
    elif sortedCounts[sortedCountsKeys[0]] == 3 and len(sortedCounts) > 1 and sortedCounts[sortedCountsKeys[1]] == 2:
        return 5, hand
    elif sortedCounts[sortedCountsKeys[0]] == 3:
        return 4, hand
    elif sortedCounts[sortedCountsKeys[0]] == 2 and len(sortedCounts) > 1 and sortedCounts[sortedCountsKeys[1]] == 2:
        return 3, hand
    elif sortedCounts[sortedCountsKeys[0]] == 2:
        return 2, hand
    else:
        return 1, hand


def part2():
    hands = []

    for line in lines:
        hand, bid = line.split()
        hand = (hand
                .replace('T', chr(ord('9') + 1))
                .replace('Q', chr(ord('9') + 3))
                .replace('K', chr(ord('9') + 4))
                .replace('A', chr(ord('9') + 5)))
        hands.append((hand, bid))

    sortedHands = sorted(hands, key=lambda handTuple: sortPart2(handTuple[0]))

    result = 0
    for handIndex, hand in enumerate(sortedHands):
        result += (handIndex + 1) * int(hand[1])
    return result


print("Part 1")
print(round(timeit.timeit('print(part1())', globals=globals(), number=1) * 1000, 4), 'ms\n')
print("Part 2")
print(round(timeit.timeit('print(part2())', globals=globals(), number=1) * 1000, 4), 'ms')
