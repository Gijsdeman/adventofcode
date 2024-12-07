#ifndef DAY03_H
#define DAY03_H
#include <core.h>

class Day03 final : public core::Day {
public:
  int64_t part1(std::ifstream &file) override;

  int64_t part2(std::ifstream &file) override;
};

static const core::DayRegistrar registerDay("3", []() -> core::Day * {
  return new Day03();
});

#endif // DAY03_H
