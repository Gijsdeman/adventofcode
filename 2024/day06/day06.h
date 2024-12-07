#ifndef DAY06_H
#define DAY06_H
#include <core.h>
#include <set>

class Day06 final : public core::Day {
public:
  int64_t part1(std::ifstream &file) override;

  int64_t part2(std::ifstream &file) override;

  static const std::vector<std::pair<int32_t, int32_t>> directions;

private:
  static std::tuple<int32_t, int32_t, std::pair<int32_t, int32_t>>
  getStartPos(const std::vector<std::string> &grid);

  static std::set<std::pair<int32_t, int32_t>>
  getPositions(const std::vector<std::string> &grid);
};

static const core::DayRegistrar registerDay("6", []() -> core::Day * {
  return new Day06();
});

#endif // DAY06_H
