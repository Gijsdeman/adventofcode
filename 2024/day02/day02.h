#ifndef DAY02_H
#define DAY02_H
#include <util.h>

class Day02 final : public util::Day {
public:
    int64_t part1(std::ifstream &file) override;

    int64_t part2(std::ifstream &file) override;
};

static const util::DayRegistrar registerDay("2", []() -> util::Day* {
    return new Day02();
});

#endif //DAY02_H
