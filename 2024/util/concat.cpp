#include "util.h"
#include <cmath>

ulong util::concatenate(const uint64_t first, const uint64_t second) {
  const int numDigits =
      second == 0 ? 1 : static_cast<int>(std::log10(second)) + 1;
  return first * static_cast<uint64_t>(std::pow(10, numDigits)) + second;
}

std::pair<bool, uint64_t> util::decatenate(const uint64_t number, const uint64_t end) {
  int divisor = 1;
  while (end / divisor > 0) {
    divisor *= 10;
  }
  return {number % divisor == end, number / divisor};
}