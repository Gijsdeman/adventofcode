#include "day07.h"

#include <deque>
#include <fstream>
#include <sstream>
#include <util.h>

bool Day07::isValid(std::deque<std::int64_t> &sequence,
                    const std::int64_t target, const bool concat) {
  const std::int64_t first = sequence.front();
  sequence.pop_front();
  if (sequence.empty()) {
    sequence.push_front(first);
    return first == target;
  }
  const std::int64_t second = sequence.front();
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

bool Day07::isValidFast(std::deque<std::int64_t> &sequence,
                        const std::int64_t target, const bool concat) {
  if (sequence.size() == 1)
    return sequence.front() == target;

  const auto last = sequence.back();
  sequence.pop_back();

  // Check if last number can be subtracted (added)
  if (const int64_t prev = target - last; prev >= 0) {
    if (isValidFast(sequence, prev, concat))
      return true;
  }

  // Check if laster number can be divides (multiplied)
  if (target >= last && target % last == 0) {
    if (isValidFast(sequence, target / last, concat))
      return true;
  }

  // Check if last number can be decatenated (concatenated)
  if (concat) {
    if (auto [endsWith, prefix] = util::decatenate(target, last); endsWith) {
      if (isValidFast(sequence, prefix, concat))
        return true;
    }
  }

  sequence.push_back(last);
  return false;
}

int64_t Day07::part1(std::ifstream &file) {
  std::string line;
  std::int64_t result = 0;
  std::vector<std::deque<std::int64_t>> sequences;

  while (std::getline(file, line)) {
    std::istringstream lineStream(line);
    std::deque<std::int64_t> sequence;
    std::string number;
    while (lineStream >> number)
      sequence.push_back(std::stoll(number));
    sequences.push_back(sequence);
  }

  for (auto sequence : sequences) {
    const auto target = sequence.front();
    sequence.pop_front();
    // if (isValid(sequence, target)) {
    if (isValidFast(sequence, target)) {
      result += target;
    }
  }

  return result;
}

int64_t Day07::part2(std::ifstream &file) {
  std::string line;
  std::int64_t result = 0;
  std::vector<std::deque<std::int64_t>> sequences;

  while (std::getline(file, line)) {
    std::istringstream lineStream(line);
    std::deque<std::int64_t> sequence;
    std::string number;
    while (lineStream >> number)
      sequence.push_back(std::stoll(number));
    sequences.push_back(sequence);
  }

  for (auto sequence : sequences) {
    const auto target = sequence.front();
    sequence.pop_front();
    // if (isValid(sequence, target, true)) {
    if (isValidFast(sequence, target, true)) {
      result += target;
    }
  }

  return result;
}
