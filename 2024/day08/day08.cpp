#include "day08.h"

#include <bitset>
#include <fstream>
#include <ranges>

Day08::gridInfo Day08::parseGrid(std::ifstream &file) {
  std::string line;
  std::vector<std::string> grid;

  while (std::getline(file, line)) {
    grid.push_back(line);
  }

  std::map<char, std::vector<std::pair<int8_t, int8_t>>> nodes;

  const short rows = grid.size();
  const short cols = grid[0].size();
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (grid[i][j] != '.') {
        if (!nodes.contains(grid[i][j])) {
          nodes[grid[i][j]] = {{i, j}};
        } else {
          nodes[grid[i][j]].emplace_back(i, j);
        }
      }
    }
  }

  return std::make_tuple(rows, cols, nodes);
}

int64_t Day08::countNodes(std::ifstream &file, const bool part2) {
  auto [rows, cols, nodes] = parseGrid(file);
  std::bitset<2550> interfere;

  for (auto const &positions : std::views::values(nodes)) {
    for (auto [row1, col1] : positions) {
      if (part2)
        interfere.set(row1 * cols + col1);
      for (auto [row2, col2] : positions) {
        if (row1 != row2 && col1 != col2) {
          const int8_t rowDir = abs(row1 - row2);
          const int8_t colDir = abs(col1 - col2);

          int8_t antiRow = row1, antiCol = col1;
          do {
            if (row1 > row2) {
              antiRow = antiRow + rowDir;
            } else {
              antiRow = antiRow - rowDir;
            }

            if (col1 > col2) {
              antiCol = antiCol + colDir;
            } else {
              antiCol = antiCol - colDir;
            }

            if (antiRow < 0 || antiRow >= rows || antiCol < 0 ||
                antiCol >= cols)
              break;

            interfere.set(antiRow * cols + antiCol);

          } while (part2);
        }
      }
    }
  }
  return interfere.count();
}

int64_t Day08::part1(std::ifstream &file) { return countNodes(file, false); }

int64_t Day08::part2(std::ifstream &file) { return countNodes(file, true); }
