#ifndef DAY02_H
#define DAY02_H
#include <core.h>

class Day02 final : public core::Day {
public:
  int64_t part1(std::ifstream &file) override;

  int64_t part2(std::ifstream &file) override;
};

static const core::DayRegistrar registerDay("2", []() -> core::Day * {
  return new Day02();
});

#endif // DAY02_H
