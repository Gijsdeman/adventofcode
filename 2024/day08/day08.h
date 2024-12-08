#ifndef DAY08_H
#define DAY08_H
#include <core.h>

#include "../util/util.h"

class Day08 final : public core::Day {
public:
  int64_t part1(std::ifstream &file) override;

  int64_t part2(std::ifstream &file) override;

private:
  using mappedVectors = std::map<char, std::vector<std::pair<int8_t, int8_t>>>;
  using gridInfo = std::tuple<int8_t, int8_t, mappedVectors>;

  static gridInfo parseGrid(std::ifstream &file);

  static uint64_t countNodes(std::ifstream &file, const bool part2);
};

static const core::DayRegistrar registerDay("8", []() -> core::Day * {
  return new Day08();
});

#endif // DAY08_H
