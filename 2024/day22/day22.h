#ifndef DAY22_H
#define DAY22_H
#include <core.h>

class Day22 final : public core::Day {
public:
  int64_t part1(std::ifstream &file) override;

  int64_t part2(std::ifstream &file) override;

private:
  static int32_t getNext(int32_t current);
};

static const core::DayRegistrar registerDay("22", []() -> core::Day * {
  return new Day22();
});

#endif // DAY22_H
