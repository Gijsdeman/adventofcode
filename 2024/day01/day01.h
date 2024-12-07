#ifndef DAY01_H
#define DAY01_H
#include <core.h>

class Day01 final : public core::Day {
public:
  int64_t part1(std::ifstream &file) override;

  int64_t part2(std::ifstream &file) override;
};

static const core::DayRegistrar registerDay("1", []() -> core::Day * {
  return new Day01();
});

#endif // DAY01_H
