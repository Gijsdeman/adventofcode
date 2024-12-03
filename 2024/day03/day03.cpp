#include <fstream>
#include <iostream>
#include <vector>
#include <regex>

#include "day03.h"

int64_t Day03::part1(std::ifstream &file)  {
  std::string line;
  int64_t result = 0;

  while (std::getline(file, line)) {
    std::regex pattern(R"(mul\((\d+),(\d+)\))");

    const auto matches_begin = std::sregex_iterator(line.begin(), line.end(), pattern);
    auto matches_end = std::sregex_iterator();

    for (std::sregex_iterator i = matches_begin; i != matches_end; ++i) {
      const std::smatch& match = *i;
      result += std::stoi(match.str(1)) * std::stoi(match.str(2));
    }

  }
  return result;
}

int64_t Day03::part2(std::ifstream &file)  {
  std::string line;
  int64_t result = 0;

  bool enabled = true;
  while (std::getline(file, line)) {
    std::regex pattern(R"(mul\((\d+),(\d+)\)|(do\(\))|(don't\(\)))");

    const auto matches_begin = std::sregex_iterator(line.begin(), line.end(), pattern);
    auto matches_end = std::sregex_iterator();

    for (std::sregex_iterator i = matches_begin; i != matches_end; ++i) {
      if (const std::smatch& match = *i; !match.str(3).empty()) {
        enabled = true;
      } else if (!match.str(4).empty()) {
        enabled = false;
      } else if (enabled) {
        result += std::stoi(match.str(1)) * std::stoi(match.str(2));
      }
    }
  }
  return result;
}
