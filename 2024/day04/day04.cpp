#include <fstream>
#include <iostream>
#include <vector>
#include <regex>

#include "day04.h"

bool match(const std::vector<std::string> &grid, const std::string &toMatch, const int16_t rows, const int16_t columns,
           const int16_t row, const int16_t column, const int16_t rowDir, const int16_t colDir) {
  std::string match;
  for (int dist = 0; dist < toMatch.size(); dist++) {
    if (row + rowDir * dist >= rows) return false;
    if (column + colDir * dist >= columns) return false;
    if (row + rowDir * dist < 0) return false;
    if (column + colDir * dist < 0) return false;
    if (grid[row + rowDir * dist][column + colDir * dist] != toMatch[dist]) return false;
  }
  return true;
}


int64_t Day04::part1(std::ifstream &file) {
  std::string line;
  uint16_t result = 0;
  std::vector<std::string> grid;

  while (std::getline(file, line)) {
    grid.push_back(line);
  }

  const int16_t rows = grid.size();
  const int16_t columns = grid.size();

  for (int row = 0; row < grid.size(); row++) {
    for (int col = 0; col < grid[0].size(); col++) {
      for (int rowDir = -1; rowDir <= 1; rowDir++) {
        for (int colDir = -1; colDir <= 1; colDir++) {
          if (match(grid, "XMAS", rows, columns, row, col, rowDir, colDir)) {
            result++;
          }
        }
      }
    }
  }

  return result;
}

int64_t Day04::part2(std::ifstream &file) {
  std::string line;
  uint16_t result = 0;
  std::vector<std::string> grid;

  while (std::getline(file, line)) {
    grid.push_back(line);
  }

  const int16_t rows = grid.size();
  const int16_t columns = grid[0].size();

  for (int row = 0; row < static_cast<int16_t>(grid.size()); row++) {
    for (int col = 0; col < grid[0].size(); col++) {
      if (match(grid, "MAS", rows, columns, row + 1, col + 1, -1, -1) || match(
            grid, "MAS", rows, columns, row - 1, col - 1, 1, 1)) {
        if (match(grid, "MAS", rows, columns, row - 1, col + 1, 1, -1) || match(
              grid, "MAS", rows, columns, row + 1, col - 1, -1, 1)) {
          result++;
        }
      }
    }
  }

  return result;
}
