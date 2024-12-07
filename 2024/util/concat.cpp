#include "util.h"
#include <cmath>

ulong util::concatenate(const uint64_t first, const uint64_t second) {
  const int numDigits =
      second == 0 ? 1 : static_cast<int>(std::log10(second)) + 1;
  return first * static_cast<uint64_t>(std::pow(10, numDigits)) + second;
}
