#include <iomanip>
#include <sstream>

#include "util.h"

std::string util::formatDay(const std::string &input) {
  std::stringstream formatStream;
  formatStream << "day" << std::setw(2) << std::setfill('0') << input;
  return formatStream.str();
}
