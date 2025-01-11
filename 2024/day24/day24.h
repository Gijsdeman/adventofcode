#ifndef DAY24_H
#define DAY24_H
#include <core.h>
#include <queue>
#include <set>

class Day24 final : public core::Day {
public:
  int64_t part1(std::ifstream &file) override;

  int64_t part2(std::ifstream &file) override;

  static const std::vector<std::pair<int32_t, int32_t>> directions;

private:
  static bool computeGate(const std::string &op, bool a, bool b);

  static void getZ(std::queue<std::vector<std::string>> &toCheck,
                   std::map<std::string, bool> &gates,
                   std::map<std::string, bool> &z);

  static void parseInput(std::ifstream &file,
                         std::queue<std::vector<std::string>> &toCheck,
                         std::map<std::string, bool> &gates);

  static bool wrongOperator(const std::string &op, const std::string &left,
                            const std::string &right);

  static void checkOperatorCombination(const std::set<std::string> &set,
                                       const std::string &left,
                                       const std::string &right,
                                       std::set<std::string> &wrong);
};

static const core::DayRegistrar registerDay("24", []() -> core::Day * {
  return new Day24();
});

#endif // DAY24_H
