#ifndef DAY13_H
#define DAY13_H
#include <core.h>

class Day13 final : public core::Day {
public:
  int64_t part1(std::ifstream &file) override;

  int64_t part2(std::ifstream &file) override;

private:
  static int64_t calculateTokens(std::ifstream &file, long addition);

  static void processPush(long &result, std::pair<long, long> &A,
                          std::pair<long, long> &B,
                          std::pair<long, long> &target);
};

static const core::DayRegistrar registerDay("13", []() -> core::Day * {
  return new Day13();
});

#endif // DAY13_H
