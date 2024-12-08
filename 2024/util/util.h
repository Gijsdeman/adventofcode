#ifndef UTIL_H
#define UTIL_H
#include <cstdint>
#include <utility>

namespace util {
uint64_t concatenate(uint64_t first, uint64_t second);
std::pair<bool, uint64_t> decatenate(uint64_t number, uint64_t end);
} // namespace util

#endif // UTIL_H
