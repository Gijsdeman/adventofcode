import timeit

file = open('input', 'r').read().strip()
lines = file.split('\n')
sections = file.split('\n\n')
grid = [[char for char in row] for row in lines]

allMaps = [{} for i in range(0, 7)]


def part1():
    seeds = sections[0].split(': ')[1]
    seeds = seeds.split()

    results = []
    for seed in seeds:
        for index, section in enumerate(sections[1:]):
            section = section.split(':\n')[1]
            maps = section.split('\n')
            for currentMap in maps:
                currentMap = currentMap.split()
                if int(currentMap[1]) <= int(seed) <= int(currentMap[1]) + int(currentMap[2]):
                    seed = int(seed) + int(currentMap[0]) - int(currentMap[1])
                    break
        results.append(seed)
    return min(results)


def part2():
    seeds = sections[0].split(': ')[1]
    seeds = seeds.split()

    sectionSeeds = []

    # Make list of seed ranges (start, stop)
    for seedIndex in range(0, len(seeds), 2):
        sectionSeeds.append((int(seeds[seedIndex]), int(seeds[seedIndex]) + int(seeds[seedIndex + 1])))

    # Consider each section
    for section in sections[1:]:
        newSection = section.split(':\n')[1]
        maps = newSection.split('\n')

        remainingSeeds = sectionSeeds
        sectionSeeds = []
        # Consider each map
        for currentMap in maps:
            currentMap = currentMap.split()
            newRemainingSeeds = []

            # Consider list of current
            while len(remainingSeeds) > 0:
                startSeed, stopSeed = remainingSeeds.pop(0)

                difference = int(currentMap[0]) - int(currentMap[1])
                mapSource = int(currentMap[1])
                mapEnd = int(currentMap[1]) + int(currentMap[2])

                # If seed range fully enclosed; whole seed range can be mapped
                if mapSource <= startSeed < stopSeed <= mapEnd:
                    sectionSeeds.append((startSeed + difference, stopSeed + difference))

                # If seed range starts earlier than map range
                # Add first part to remaining, add latter part to section
                elif startSeed < mapSource < stopSeed <= mapEnd:
                    newRemainingSeeds.append((startSeed, mapSource))
                    sectionSeeds.append((mapSource + difference, stopSeed + difference))

                # If seed range end later than map range
                # Add first part to section, add latter part to remaining
                elif mapSource <= startSeed < mapEnd < stopSeed:
                    newRemainingSeeds.append((mapEnd, stopSeed))
                    sectionSeeds.append((startSeed + difference, mapEnd + difference))

                # If seed range surrounds map range
                # Add first and latter part to remaining, add middle to section
                elif startSeed < mapSource <= mapEnd < stopSeed:
                    newRemainingSeeds.append((startSeed, mapSource))
                    newRemainingSeeds.append((mapEnd, stopSeed))
                    sectionSeeds.append((mapSource + difference, mapEnd + difference))

                # Otherwise, no part of range is mapped, so add all to remaining
                else:
                    newRemainingSeeds.append((startSeed, stopSeed))

            # If there are any remaining seeds, consider them for the next map
            remainingSeeds = newRemainingSeeds
        # Any seeds that could not be mapped, can be added to section again
        sectionSeeds += remainingSeeds
    return min(sectionSeeds)[0]


print("Part 1")
print(round(timeit.timeit('print(part1())', globals=globals(), number=1) * 1000, 4), 'ms\n')
print("Part 2")
print(round(timeit.timeit('print(part2())', globals=globals(), number=1) * 1000, 4), 'ms')
