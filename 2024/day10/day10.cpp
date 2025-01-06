#include "day10.h"

#include <fstream>
#include <queue>
#include <set>

const std::vector<std::pair<int32_t, int32_t>> Day10::directions = {
    {-1, 0}, {0, 1}, {1, 0}, {0, -1}};

std::tuple<int32_t, int32_t, std::vector<std::pair<int32_t, int32_t>>>
Day10::getStartPositions(const std::vector<std::string> &grid) {
  std::vector<std::pair<int32_t, int32_t>> positions;
  const short rows = grid.size();
  const short cols = grid[0].size();
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (grid[i][j] == '0') {
        positions.push_back({i, j});
      }
    }
  }
  return {rows, cols, positions};
}

uint16_t Day10::countPaths(std::ifstream &file, bool part2) {
  std::string line;
  std::vector<std::string> grid;
  uint16_t result = 0;

  while (std::getline(file, line)) {
    grid.push_back(line);
  }
  const auto [rows, cols, positions] = getStartPositions(grid);

  std::queue<std::tuple<int16_t, int16_t, int16_t>> queue;
  std::set<std::pair<int16_t, int16_t>> visited;

  for (auto [x, y] : positions) {
    std::queue<std::tuple<int16_t, int16_t, int16_t>> empty;
    std::swap(queue, empty);
    queue.push({x, y, 0});
    if (!part2)
      visited.clear();

    while (!queue.empty()) {
      const auto [xp, yp, hp] = queue.front();
      queue.pop();

      for (int d = 0; d < 4; d++) {
        int16_t xn = xp + directions[d].first;
        int16_t yn = yp + directions[d].second;

        if (xn < 0 || xn >= rows || yn < 0 || yn >= cols) {
          continue;
        }

        if (grid[xn][yn] - '0' != hp + 1) {
          continue;
        }

        if (grid[xn][yn] == '9') {
          if (!part2) {
            if (!visited.contains({xn, yn})) {
              visited.insert({xn, yn});
              result += 1;
            }
          } else {
            result += 1;
          }
          continue;
        }

        queue.push({xn, yn, hp + 1});
      }
    }
  }

  return result;
}

int64_t Day10::part1(std::ifstream &file) { return countPaths(file, false); }

int64_t Day10::part2(std::ifstream &file) { return countPaths(file, true); }