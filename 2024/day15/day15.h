#ifndef DAY15_H
#define DAY15_H
#include <core.h>
#include <cstdint>

class Day15 final : public core::Day {
public:
  int64_t part1(std::ifstream &file) override;

  int64_t part2(std::ifstream &file) override;

private:
  static void parseInput(std::ifstream &file, std::vector<std::string> &grid,
                         std::pair<uint32_t, uint32_t> &currentPos, bool part2);

  static void walk(std::ifstream &file, std::vector<std::string> &grid,
                   std::pair<uint32_t, uint32_t> &currentPos);

  static int32_t getScore(const std::vector<std::string> &grid);
};

static const core::DayRegistrar registerDay("15", []() -> core::Day * {
  return new Day15();
});

#endif // DAY15_H
