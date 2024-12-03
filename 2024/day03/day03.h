#ifndef DAY03_H
#define DAY03_H
#include <util.h>

class Day03 final : public util::Day {
public:
    int64_t part1(std::ifstream &file) override;

    int64_t part2(std::ifstream &file) override;
};

static const util::DayRegistrar registerDay("3", []() -> util::Day* {
    return new Day03();
});


#endif //DAY03_H
