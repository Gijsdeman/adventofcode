#include <cmath>
#include <cstdint>

#include "util.h"

ulong util::concatenate(const uint64_t first, const uint64_t second) {
  return first * static_cast<uint64_t>(std::pow(10, countDigits(second))) +
         second;
}

std::pair<bool, uint64_t> util::decatenate(const uint64_t number,
                                           const uint64_t end) {
  int divisor = 1;
  while (end / divisor > 0) {
    divisor *= 10;
  }
  return {number % divisor == end, number / divisor};
}