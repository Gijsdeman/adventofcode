#ifndef UTIL_H
#define UTIL_H

#include <functional>
#include <map>
#include <string>

namespace util {
    class Day {
    public:
        virtual ~Day() = default;

        virtual int64_t part1(std::ifstream &file) = 0;

        virtual int64_t part2(std::ifstream &file) = 0;

    protected:
        std::string input;
    };

    class DayFactory {
    public:
        using Creator = std::function<Day*()>;

        static DayFactory &instance();

        void registerDay(const std::string &day, Creator creator);

        Day *createDay(const std::string &day);

    private:
        std::map<std::string, Creator> creators_;
    };

    class DayRegistrar {
    public:
        DayRegistrar(const std::string &day, const DayFactory::Creator &creator);
    };

    void fetchInput(const std::string &path, const std::string &day);

    void fetchExamples(const std::string &path, const std::string &day);

    int64_t timeExecution(Day *day, const std::string &part, int64_t (Day::*func)(std::ifstream &),
                          std::ifstream &file);

    Day *loadDayInstance(const std::string &day);

    std::string formatDay(const std::string &input);
}

#endif //UTIL_H
