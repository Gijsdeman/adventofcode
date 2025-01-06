#include "day25.h"

#include <fstream>

std::vector<uint8_t>
Day25::processSection(const std::vector<std::string> &section) {
  std::vector<uint8_t> counts(5, 0);
  for (const auto &line : section) {
    for (int i = 0; i < line.size(); ++i) {
      if (line[i] == '#') {
        counts[i]++;
      }
    }
  }
  return counts;
}

int64_t Day25::part1(std::ifstream &file) {
  std::string line;
  std::vector<std::vector<uint8_t>> keys;
  std::vector<std::vector<uint8_t>> locks;

  std::vector<std::vector<std::string>> sections;
  std::vector<std::string> ifsection;

  while (std::getline(file, line)) {
    if (line.empty()) {
      sections.push_back(ifsection);
      ifsection.clear();
    } else {
      ifsection.push_back(line);
    }
  }
  sections.push_back(ifsection);

  for (const auto &section : sections) {
    if (section[0] == "#####") {
      locks.push_back(processSection(section));
    } else {
      keys.push_back(processSection(section));
    }
  }

  uint16_t result = 0;
  for (const auto &lock : locks) {
    for (const auto &key : keys) {
      bool isValid = true;
      for (int i = 0; i < key.size(); ++i) {
        if (key[i] + lock[i] > 7) {
          isValid = false;
          break;
        }
      }
      if (isValid) {
        ++result;
      }
    }
  }

  return result;
}

int64_t Day25::part2(std::ifstream &file) { return 0; }
