#ifndef UTIL_H
#define UTIL_H
#include <utility>

namespace util {
uint64_t concatenate(uint64_t first, uint64_t second);
std::pair<bool, uint64_t> decatenate(uint64_t number, uint64_t end);

uint8_t countDigits(uint64_t number);
uint64_t powerOf10(uint8_t exponent);
} // namespace util

#endif // UTIL_H
