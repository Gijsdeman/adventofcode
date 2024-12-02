#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

#include "day02.h"

static bool isValid(std::vector<int16_t> sequence) {
  std::vector<int16_t> sorted = sequence;

  // Increasing
  std::ranges::sort(sorted, std::less<>());
  bool valid = std::ranges::equal(sorted, sequence);
  // Decreasing
  std::ranges::sort(sorted, std::greater<>());
  valid = valid || std::ranges::equal(sorted, sequence);

  if (!valid) return false;

  // Differences
  for (int i = 1; i < sorted.size(); i++) {
    const int16_t diff = abs(sorted[i] - sorted[i - 1]);
    valid = valid && diff > 0 && diff <= 3;
  }
  return valid;
}

int64_t Day02::part1(std::ifstream &file)  {
  std::string line;
  uint16_t result = 0;
  while (std::getline(file, line)) {
    std::istringstream lineStream(line);

    std::vector<int16_t> sequence;
    uint16_t currentNumber;

    while (lineStream >> currentNumber) {
      sequence.push_back(currentNumber);
    }

    if (isValid(sequence)) {
      result++;
    }
  }
  return result;
}

int64_t Day02::part2(std::ifstream &file)  {
  std::string line;
  uint16_t result = 0;
  while (std::getline(file, line)) {
    std::istringstream lineStream(line);

    std::vector<int16_t> sequence;
    uint16_t currentNumber;

    while (lineStream >> currentNumber) {
      sequence.push_back(currentNumber);
    }

    for (int i = 0; i < sequence.size(); i++) {
      std::vector<int16_t> newSequence = sequence;
      newSequence.erase(newSequence.begin() + i);
      if (isValid(newSequence)) {
        result++;
        break;
      }
    }
  }
  return result;
}
