#ifndef DAY01_H
#define DAY01_H
#include <util.h>

class Day01 final : public util::Day {
public:
    int64_t part1(std::ifstream &file) override;

    int64_t part2(std::ifstream &file) override;
};

static const util::DayRegistrar registerDay("1", []() -> util::Day* {
    return new Day01();
});

#endif //DAY01_H
