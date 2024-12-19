#include <bitset>
#include <deque>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "day19.h"

std::unordered_map<std::string, uint64_t> possible;

uint64_t Day19::getOptions(const std::string &line,
                           std::vector<std::string> &tokens) {
  if (possible.contains(line)) {
    return possible[line];
  }
  if (line.empty()) {
    return possible[line] = 1;
  }

  uint64_t result = 0;
  for (auto &token : tokens) {
    if (const auto tokenSize = token.size();
        line.size() >= tokenSize && line.compare(0, tokenSize, token) == 0) {
      result += getOptions(line.substr(tokenSize), tokens);
    }
  }

  return possible[line] = result;
}

int64_t Day19::part1(std::ifstream &file) {
  std::string line;
  std::vector<std::string> tokens;

  std::getline(file, line);
  std::stringstream lineStream(line);
  std::string token;

  while (std::getline(lineStream, token, ',')) {
    auto end_pos = std::remove(token.begin(), token.end(), ' ');
    token.erase(end_pos, token.end());
    tokens.push_back(token);
  }
  std::getline(file, line);

  int result = 0;
  while (std::getline(file, line)) {
    if (getOptions(line, tokens) > 0) {
      result++;
    }
  }

  return result;
}

int64_t Day19::part2(std::ifstream &file) {
  std::string line;
  std::vector<std::string> tokens;

  std::getline(file, line);
  std::stringstream lineStream(line);
  std::string token;

  while (std::getline(lineStream, token, ',')) {
    auto end_pos = std::remove(token.begin(), token.end(), ' ');
    token.erase(end_pos, token.end());
    tokens.push_back(token);
  }
  std::getline(file, line);

  uint64_t result = 0;
  std::vector<std::string> bestOption;
  while (std::getline(file, line)) {
    result += getOptions(line, tokens);
  }

  return result;
}