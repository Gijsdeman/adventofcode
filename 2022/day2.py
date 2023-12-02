file = open('day2.input', 'r')
lines = file.readlines()

map = {
    'X': 'A',
    'Y': 'B',
    'Z': 'C'
}

draw = {
    'A': 'X',
    'B': 'Y',
    'C': 'Z'
}

win = {
    'A': 'Y',
    'B': 'Z',
    'C': 'X'
}

lose = {
    'A': 'Z',
    'B': 'X',
    'C': 'Y'
}

score = {
    'X': 1,
    'Y': 2,
    'Z': 3
}

outerScore = 0

# For challenge 1
# for game in lines:
#     options = game.split()
#     innerScore = 0
#     if win[options[0]] == options[1]:
#         innerScore += 6
#     elif options[0] == draw[options[1]]:
#         innerScore += 3
#     innerScore += score[options[1]]
#     outerScore += innerScore

# For challenge 2
for game in lines:
    options = game.split()
    innerScore = 0
    if options[1] == 'X':
        # Lose
        innerScore += score[lose[options[0]]]
    elif options[1] == 'Y':
        # Draw
        innerScore += 3
        innerScore += score[draw[options[0]]]
    else:
        # Win
        innerScore += 6
        innerScore += score[win[options[0]]]
    outerScore += innerScore

print(outerScore)