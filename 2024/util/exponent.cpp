#include <cstdint>

#include "util.h"

uint8_t util::countDigits(uint64_t number) {
  int digits = 1;
  while (number >= 10) {
    number /= 10;
    ++digits;
  }
  return digits;
}

uint64_t util::powerOf10(uint8_t exponent) {
  uint64_t result = 1;
  while (exponent--)
    result *= 10;
  return result;
}
