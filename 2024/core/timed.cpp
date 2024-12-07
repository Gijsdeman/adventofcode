#include "core.h"

#include <chrono>
#include <functional>
#include <iostream>

int64_t core::timeExecution(Day *day, const std::string &part,
                            int64_t (Day::*func)(std::ifstream &),
                            std::ifstream &file) {
  const auto start = std::chrono::high_resolution_clock::now();
  const auto result = (day->*func)(file);
  const auto end = std::chrono::high_resolution_clock::now();
  const std::chrono::duration<double, std::milli> ms_double = end - start;
  std::cout << part << ": " << ms_double.count() << "ms" << std::endl;
  return result;
}
