#ifndef DAY04_H
#define DAY04_H
#include <core.h>

class Day04 final : public core::Day {
public:
  int64_t part1(std::ifstream &file) override;

  int64_t part2(std::ifstream &file) override;
};

static const core::DayRegistrar registerDay("4", []() -> core::Day * {
  return new Day04();
});

#endif // DAY04_H
