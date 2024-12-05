#ifndef DAY05_H
#define DAY05_H
#include <set>
#include <util.h>

class Day05 final : public util::Day {
public:
  using orderMap = std::map<std::string, std::set<std::string>>;
  using sequenceList = std::vector<std::vector<std::string>>;

  struct order {
    orderMap &after;

    bool operator()(const std::string &a, const std::string &b) const {
      if (const auto it = after.find(a); it != after.end()) {
        return it->second.contains(b);
      }
      return false;
    }
  };

  static std::pair<orderMap, sequenceList> parseInput(std::ifstream &file);

  int64_t part1(std::ifstream &file) override;

  int64_t part2(std::ifstream &file) override;
};

static const util::DayRegistrar registerDay("5", []() -> util::Day * {
  return new Day05();
});

#endif // DAY05_H
