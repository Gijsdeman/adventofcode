#ifndef DAY14_H
#define DAY14_H
#include <core.h>

class Day14 final : public core::Day {
public:
  int64_t part1(std::ifstream &file) override;

  int64_t part2(std::ifstream &file) override;

private:
  static void parseInput(std::ifstream &file,
                         std::vector<std::pair<int32_t, int32_t>> &points,
                         std::vector<std::pair<int32_t, int32_t>> &vectors);

  static uint32_t wrap(int32_t value, int32_t mod);
};

static const core::DayRegistrar registerDay("14", []() -> core::Day * {
  return new Day14();
});

#endif // DAY14_H
