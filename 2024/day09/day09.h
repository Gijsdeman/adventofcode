#ifndef DAY09_H
#define DAY09_H
#include <core.h>

class Day09 final : public core::Day {
public:
  int64_t part1(std::ifstream &file) override;

  int64_t part2(std::ifstream &file) override;
};

static const core::DayRegistrar registerDay("9", []() -> core::Day * {
  return new Day09();
});

#endif // DAY09_H
