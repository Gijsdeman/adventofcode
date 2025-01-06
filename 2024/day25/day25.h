#ifndef DAY25_H
#define DAY25_H
#include <core.h>

class Day25 final : public core::Day {
public:
  int64_t part1(std::ifstream &file) override;

  int64_t part2(std::ifstream &file) override;

private:
  std::vector<uint8_t> processSection(const std::vector<std::string> &section);
};

static const core::DayRegistrar registerDay("25", []() -> core::Day * {
  return new Day25();
});

#endif // DAY25_H
