file = open('day6.input', 'r')
lines = file.readlines()
import math

result = 1

times = lines[0].split(":")[1].split()
distances = lines[1].split(":")[1].split()

for index in range(0, len(times)):
    innerResult = 0;
    raceTime = times[index]
    record = distances[index]
    for timePressed in range(0, int(raceTime)):
        potentialRecord = timePressed * (int(raceTime) - timePressed)
        if potentialRecord > int(record):
            innerResult += 1
    result *= innerResult

print("Part 1")
print(int(result))
print("")

result = 0

time = ''.join(lines[0].split(":")[1].split())
distance = ''.join(lines[1].split(":")[1].split())

for timePressed in range(0, int(time)):
    potentialRecord = timePressed * (int(time) - timePressed)
    if potentialRecord > int(distance):
        result += 1

print("Part 2")
print(result)
print("")

result = 0

time = int(''.join(lines[0].split(":")[1].split()))
distance = int(''.join(lines[1].split(":")[1].split()))

lower = math.floor(0.5 * (time - math.sqrt(time * time - 4 * distance)))
upper = math.floor(0.5 * (time + math.sqrt(time * time - 4 * distance)))

print("Part 2 - derivative")
print(upper-lower)