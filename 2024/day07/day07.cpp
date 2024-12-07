#include <fstream>
#include <iostream>
#include <regex>
#include <vector>

#include "day07.h"

bool Day07::isValid(std::deque<std::uint64_t> &sequence,
                    const std::uint64_t target, const bool concat) {
  const std::uint64_t first = sequence.front();
  sequence.pop_front();
  if (sequence.empty()) {
    sequence.push_front(first);
    return first == target;
  }
  const std::uint64_t second = sequence.front();
  sequence.pop_front();

  sequence.push_front(first + second);
  if (isValid(sequence, target, concat))
    return true;
  sequence.pop_front();

  sequence.push_front(first * second);
  if (isValid(sequence, target, concat))
    return true;
  sequence.pop_front();

  if (concat) {
    sequence.push_front(util::concatenate(first, second));
    if (isValid(sequence, target, concat))
      return true;
    sequence.pop_front();
  }
  sequence.push_front(second);
  sequence.push_front(first);

  return false;
}

int64_t Day07::part1(std::ifstream &file) {
  std::string line;
  std::uint64_t result = 0;
  std::vector<std::deque<std::uint64_t>> sequences;

  while (std::getline(file, line)) {
    std::istringstream lineStream(line);
    std::deque<std::uint64_t> sequence;
    std::string number;
    while (lineStream >> number)
      sequence.push_back(std::stoull(number));
    sequences.push_back(sequence);
  }

  for (auto sequence : sequences) {
    const auto target = sequence.front();
    sequence.pop_front();
    if (isValid(sequence, target)) {
      result += target;
    }
  }

  return result;
}

int64_t Day07::part2(std::ifstream &file) {
  std::string line;
  std::uint64_t result = 0;
  std::vector<std::deque<std::uint64_t>> sequences;

  while (std::getline(file, line)) {
    std::istringstream lineStream(line);
    std::deque<std::uint64_t> sequence;
    std::string number;
    while (lineStream >> number)
      sequence.push_back(std::stoull(number));
    sequences.push_back(sequence);
  }

  for (auto sequence : sequences) {
    const auto target = sequence.front();
    sequence.pop_front();
    if (isValid(sequence, target, true)) {
      result += target;
    }
  }

  return result;
}
