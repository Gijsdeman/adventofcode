#ifndef DAY12_H
#define DAY12_H
#include <bitset>
#include <core.h>
#include <set>

class Day12 final : public core::Day {
public:
  int64_t part1(std::ifstream &file) override;

  int64_t part2(std::ifstream &file) override;
  static const std::vector<std::pair<int8_t, int8_t>> directions;

private:
  using perimeterMap = std::map<int8_t, std::set<std::pair<int32_t, int32_t>>>;
};

static const core::DayRegistrar registerDay("12", []() -> core::Day * {
  return new Day12();
});

#endif // DAY12_H
