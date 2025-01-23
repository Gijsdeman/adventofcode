#ifndef DAY11_H
#define DAY11_H
#include <core.h>
#include <cstdint>

class Day11 final : public core::Day {
public:
  int64_t part1(std::ifstream &file) override;

  int64_t part2(std::ifstream &file) override;

private:
  std::unordered_map<uint64_t, uint64_t> cache;
  uint64_t countStones(std::ifstream &file, uint8_t depth);
  uint64_t splitStone(uint64_t label, uint8_t depth);
};

static const core::DayRegistrar registerDay("11", []() -> core::Day * {
  return new Day11();
});

#endif // DAY11_H
