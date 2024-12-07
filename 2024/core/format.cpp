#include <iomanip>
#include <sstream>

#include "core.h"

std::string core::formatDay(const std::string &input) {
  std::stringstream formatStream;
  formatStream << "day" << std::setw(2) << std::setfill('0') << input;
  return formatStream.str();
}
