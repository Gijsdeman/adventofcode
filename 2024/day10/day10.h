#ifndef DAY10_H
#define DAY10_H
#include <core.h>
#include <set>

class Day10 final : public core::Day {
public:
  int64_t part1(std::ifstream &file) override;

  int64_t part2(std::ifstream &file) override;

  static const std::vector<std::pair<int32_t, int32_t>> directions;

private:
  static std::tuple<int32_t, int32_t, std::vector<std::pair<int32_t, int32_t>>>
  getStartPositions(const std::vector<std::string> &grid);

  static uint16_t countPaths(std::ifstream &file, bool part2);
};

static const core::DayRegistrar registerDay("10", []() -> core::Day * {
  return new Day10();
});

#endif // DAY10_H
