#ifndef DAY23_H
#define DAY23_H
#include <core.h>
#include <set>

class Day23 final : public core::Day {
public:
  int64_t part1(std::ifstream &file) override;

  int64_t part2(std::ifstream &file) override;

  static const std::vector<std::pair<int32_t, int32_t>> directions;

private:
  void BronKerbosch(
      const std::set<std::string> &R, std::set<std::string> &P,
      std::set<std::string> &X,
      const std::unordered_map<std::string, std::set<std::string>> &adj,
      std::vector<std::string> &clique);
};

static const core::DayRegistrar registerDay("23", []() -> core::Day * {
  return new Day23();
});

#endif // DAY23_H
