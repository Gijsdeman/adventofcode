#include "day05.h"

#include <algorithm>
#include <fstream>
#include <sstream>

std::pair<Day05::orderMap, Day05::sequenceList>
Day05::parseInput(std::ifstream &file) {
  std::string line;
  orderMap after;

  while (std::getline(file, line) && !line.empty()) {
    const uint8_t pos = line.find('|');
    after[line.substr(0, pos)].insert(line.substr(pos + 1));
  }

  sequenceList sequences;
  while (std::getline(file, line)) {
    std::stringstream stream(line);
    std::string current;
    std::vector<std::string> sequence;
    while (std::getline(stream, current, ','))
      sequence.push_back(current);
    sequences.push_back(sequence);
  }

  return std::make_pair(after, sequences);
}

int64_t Day05::part1(std::ifstream &file) {
  uint16_t result = 0;

  for (auto [after, sequences] = parseInput(file); auto sequence : sequences) {
    auto sorted = sequence;
    std::ranges::sort(sorted, order{after});

    if (std::ranges::equal(sorted, sequence)) {
      result += std::stoi(sequence[sequence.size() / 2]);
    }
  }

  return result;
}

int64_t Day05::part2(std::ifstream &file) {
  uint16_t result = 0;

  for (auto [after, sequences] = parseInput(file); auto sequence : sequences) {
    auto sorted = sequence;
    std::ranges::sort(sorted, order{after});

    if (!std::ranges::equal(sorted, sequence)) {
      result += std::stoi(sorted[sorted.size() / 2]);
    }
  }

  return result;
}
