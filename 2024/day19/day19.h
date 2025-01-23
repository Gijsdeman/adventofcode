#ifndef DAY19_H
#define DAY19_H
#include <core.h>
#include <cstdint>

class Day19 final : public core::Day {
public:
  int64_t part1(std::ifstream &file) override;

  int64_t part2(std::ifstream &file) override;

private:
  static uint64_t getOptions(const std::string &line,
                             std::vector<std::string> &tokens);
};

static const core::DayRegistrar registerDay("19", []() -> core::Day * {
  return new Day19();
});

#endif // DAY19_H
