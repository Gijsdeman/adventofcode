#include "day11.h"

#include <fstream>
#include <sstream>
#include <util.h>

uint64_t Day11::splitStone(const uint64_t label, const uint8_t depth) {
  if (depth == 0) {
    return 1;
  }

  const auto key = (label << 7) | depth;
  if (const auto it = cache.find(key); it != cache.end())
    return it->second;

  uint64_t result = 0;
  if (label == 0) {
    result = splitStone(1, depth - 1);
  } else if (const uint64_t digits = util::countDigits(label);
             digits % 2 == 0) {
    const uint64_t divisor = util::powerOf10(digits / 2);
    result = splitStone(label / divisor, depth - 1) +
             splitStone(label % divisor, depth - 1);
  } else {
    result = splitStone(label * 2024, depth - 1);
  }

  cache.emplace(key, result);
  return result;
}

uint64_t Day11::countStones(std::ifstream &file, const uint8_t depth) {
  std::string line;
  std::vector<uint64_t> grid;

  while (std::getline(file, line)) {
    std::istringstream lineStream(line);
    uint64_t number;

    while (lineStream >> number) {
      grid.push_back(number);
    }
  }

  uint64_t result = 0;
  for (int i = 0; i < grid.size(); i++) {
    result += splitStone(grid[i], depth);
  }
  return result;
}

int64_t Day11::part1(std::ifstream &file) {
  cache.clear();
  cache.reserve(5000);
  return countStones(file, 25);
}

int64_t Day11::part2(std::ifstream &file) {
  cache.clear();
  cache.reserve(1000000);
  return countStones(file, 75);
}
