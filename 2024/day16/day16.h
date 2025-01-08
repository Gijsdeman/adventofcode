#ifndef DAY16_H
#define DAY16_H
#include <core.h>

class Day16 final : public core::Day {
public:
  int64_t part1(std::ifstream &file) override;

  int64_t part2(std::ifstream &file) override;

  struct Point {
    int32_t x;
    int32_t y;
    int32_t d;
  };

private:
  static int32_t
  Dijkstra(const std::vector<std::string> &grid,
           std::vector<std::vector<std::vector<int32_t>>> &distance,
           bool reverse);
};

static const core::DayRegistrar registerDay("16", []() -> core::Day * {
  return new Day16();
});

#endif // DAY16_H
