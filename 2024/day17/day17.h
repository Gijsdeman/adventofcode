#ifndef DAY17_H
#define DAY17_H
#include <core.h>
#include <cstdint>

class Day17 final : public core::Day {
public:
  int64_t part1(std::ifstream &file) override;

  int64_t part2(std::ifstream &file) override;

  static const std::vector<std::pair<int32_t, int32_t>> directions;

private:
  static void parseInput(std::ifstream &file, std::vector<uint64_t> &registers,
                         std::vector<uint16_t> &operations);

  static std::vector<uint16_t>
  executeProgram(std::vector<uint64_t> &registers,
                 const std::vector<uint16_t> &operations);

  static uint64_t depthSearch(std::vector<uint16_t> &operations,
                              uint64_t currentValue, uint16_t pointer);
};

static const core::DayRegistrar registerDay("17", []() -> core::Day * {
  return new Day17();
});

#endif // DAY17_H
