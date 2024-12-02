#include <iostream>
#include <filesystem>
#include <fstream>

#include "util/util.h"

int main() {
  const std::string day = std::getenv("DAY") ? std::getenv("DAY") : "1";
  const std::string part = std::getenv("PART") ? std::getenv("PART") : "0";
  const std::string example = std::getenv("EXAMPLE") ? std::getenv("EXAMPLE") : "F";

  const std::string rootDir = std::getenv("CWD") ? std::getenv("CWD") : std::filesystem::current_path();;
  const std::string dayFolder = util::formatDay(day);
  const std::string outputType = example == "T" ? "example" : "input";
  const std::filesystem::path inputPath = std::filesystem::path(rootDir) / dayFolder / outputType;

  if (example == "F") util::fetchInput(inputPath, day);
  if (example == "T") util::fetchExamples(inputPath, day);

  util::Day* currentDay = util::loadDayInstance(day);
  if (part == "0" || part == "1") {
    std::filesystem::path outputPath = std::filesystem::path(rootDir) / dayFolder / (outputType + ".1.out");
    std::ifstream file(inputPath);
    const int64_t result1 = timeExecution(currentDay, "part 1", &util::Day::part1, file);
    std::ofstream outFile(outputPath);
    outFile << result1 << std::endl;
  }

  if (part == "0" || part == "2") {
    std::filesystem::path outputPath = std::filesystem::path(rootDir) / dayFolder / (outputType + ".2.out");
    std::ifstream file(inputPath);
    const int64_t result2 = timeExecution(currentDay, "part 2", &util::Day::part2, file);
    std::ofstream outFile2(outputPath);
    outFile2 << result2 << std::endl;
  }
}