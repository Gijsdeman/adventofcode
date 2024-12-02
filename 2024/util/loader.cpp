#include <functional>
#include <map>
#include <memory>

#include "util.h"
#include "../day01/day01.h"
#include "../day02/day02.h"

util::Day* util::loadDayInstance(const std::string& day) {
  std::map<std::string, std::function<Day*()>> days = {
    {
      "1", []() {
        return new Day01();
      }
    },
    {
      "2", []() {
        return new Day02();
      }
    },
  };

  const auto currentDay = days.find(day);
  if (currentDay == days.end()) throw std::invalid_argument("Invalid day: " + day);
  return currentDay->second();
}