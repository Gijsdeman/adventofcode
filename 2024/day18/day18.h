#ifndef DAY18_H
#define DAY18_H
#include <core.h>
#include <cstdint>

class Day18 final : public core::Day {
public:
  int64_t part1(std::ifstream &file) override;

  int64_t part2(std::ifstream &file) override;

  static const std::vector<std::pair<int32_t, int32_t>> directions;

private:
  static std::pair<bool, uint16_t>
  checkPossible(const std::vector<std::vector<char>> &grid);

  static int64_t part2naive(std::ifstream &file);
  static int64_t part2binary(std::ifstream &file);
};

static const core::DayRegistrar registerDay("18", []() -> core::Day * {
  return new Day18();
});

#endif // DAY18_H
