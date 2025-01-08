#include "day22.h"

#include <bitset>
#include <fstream>
#include <iostream>

constexpr int MAX_SEQ = 13 * 13 * 13 * 13;

int32_t Day22::getNext(int32_t current) {
  current = ((current << 6) ^ current) & 0xFFFFFF;
  current = ((current >> 5) ^ current) & 0xFFFFFF;
  current = ((current << 11) ^ current) & 0xFFFFFF;
  return current;
}

int64_t Day22::part1(std::ifstream &file) {
  std::string line;
  int64_t result = 0;
  while (std::getline(file, line)) {
    int32_t current = std::stoi(line);
    for (int i = 0; i < 2000; i++) {
      current = getNext(current);
    }
    result += current;
  }
  return result;
}

int64_t Day22::part2(std::ifstream &file) {
  std::string line;

  std::array<uint32_t, MAX_SEQ> sequences{};
  std::array<uint32_t, MAX_SEQ> total_prices{};

  while (std::getline(file, line)) {
    int32_t current = std::stoi(line);
    const uint32_t original = current;

    uint32_t prevPrice = current % 10;
    uint32_t currSequence = 0;

    for (int i = 0; i < 2000; i++) {
      current = getNext(current);

      const uint32_t currPrice = current % 10;
      const uint32_t change = currPrice - prevPrice;
      prevPrice = currPrice;

      currSequence = (currSequence * 13 + change + 9) % MAX_SEQ;
      if (sequences[currSequence] != original) {
        sequences[currSequence] = original;
        total_prices[currSequence] += prevPrice;
      }
    }
  }

  return *std::max_element(total_prices.begin(), total_prices.end());
}