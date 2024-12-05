#ifndef DAY04_H
#define DAY04_H
#include <util.h>

class Day04 final : public util::Day {
public:
  int64_t part1(std::ifstream &file) override;

  int64_t part2(std::ifstream &file) override;
};

static const util::DayRegistrar registerDay("4", []() -> util::Day * {
  return new Day04();
});

#endif // DAY04_H
