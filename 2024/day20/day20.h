#ifndef DAY20_H
#define DAY20_H
#include <core.h>
#include <cstdint>

class Day20 final : public core::Day {
public:
  int64_t part1(std::ifstream &file) override;

  int64_t part2(std::ifstream &file) override;

  static const std::vector<std::pair<int32_t, int32_t>> directions;

private:
  struct Point {
    int32_t x;
    int32_t y;
    int32_t dist;
  };

  struct GridInfo {
    uint8_t rows;
    uint8_t cols;
    int startX;
    int startY;
  };

  static uint32_t solution1;
  static uint32_t solution2;

  static GridInfo getStartPos(const std::vector<std::string> &grid);
  static void getPositions(const std::vector<std::string> &grid);
};

static const core::DayRegistrar registerDay("20", []() -> core::Day * {
  return new Day20();
});

#endif // DAY20_H
