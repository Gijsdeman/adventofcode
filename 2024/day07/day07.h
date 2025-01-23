#ifndef DAY07_H
#define DAY07_H
#include <core.h>
#include <deque>

class Day07 final : public core::Day {
public:
  int64_t part1(std::ifstream &file) override;

  int64_t part2(std::ifstream &file) override;

private:
  static bool isValid(std::deque<int64_t> &sequence, int64_t target,
                      bool concat = false);

  static bool isValidFast(std::deque<int64_t> &sequence,
                          int64_t target, bool concat = false);
};

static const core::DayRegistrar registerDay("7", []() -> core::Day * {
  return new Day07();
});

#endif // DAY07_H
