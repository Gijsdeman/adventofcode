#include "day01.h"

#include <algorithm>
#include <fstream>
#include <sstream>
#include <unordered_set>

int64_t Day01::part1(std::ifstream &file) {
  std::vector<int32_t> left;
  std::vector<int32_t> right;
  std::string line;

  while (std::getline(file, line)) {
    std::istringstream lineStream(line);
    if (int numRight, numLeft; lineStream >> numLeft >> numRight) {
      left.push_back(numLeft);
      right.push_back(numRight);
    }
  }

  std::ranges::sort(left);
  std::ranges::sort(right);

  int result = 0;
  for (int i = 0; i < left.size(); i++) {
    result += abs(left[i] - right[i]);
  }

  return result;
}

int64_t Day01::part2(std::ifstream &file) {
  std::vector<int32_t> left;
  std::vector<int32_t> right;
  std::string line;

  while (std::getline(file, line)) {
    std::istringstream lineStream(line);
    if (int numRight, numLeft; lineStream >> numLeft >> numRight) {
      left.push_back(numLeft);
      right.push_back(numRight);
    }
  }

  const std::unordered_multiset multiset(right.begin(), right.end());

  int result = 0;
  for (int currentNumber : left) {
    result += currentNumber * multiset.count(currentNumber);
  }

  return result;
}