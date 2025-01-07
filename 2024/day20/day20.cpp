#include "day20.h"

#include <deque>
#include <fstream>
#include <iostream>

uint32_t Day20::solution1 = 0;
uint32_t Day20::solution2 = 0;

const std::vector<std::pair<int32_t, int32_t>> Day20::directions = {
    {-1, 0}, {0, 1}, {1, 0}, {0, -1}};

Day20::GridInfo Day20::getStartPos(const std::vector<std::string> &grid) {
  const uint8_t rows = grid.size();
  const uint8_t cols = grid[0].size();
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (grid[i][j] == 'S') {
        return {rows, cols, i, j};
      }
    }
  }
  return {0, 0, 0, 0};
}

void Day20::getPositions(const std::vector<std::string> &grid) {
  auto [rows, cols, startX, startY] = getStartPos(grid);
  std::deque<Point> queue;
  std::vector<Point> points;

  queue.push_back({startX, startY, 0});
  points.push_back({startX, startY, 0});
  int8_t pd = -1;

  while (!queue.empty()) {
    auto &[x, y, dist] = queue.front();
    queue.pop_front();

    for (int d = 0; d < 4; d++) {
      if (pd == d) {
        continue;
      }

      const int32_t newX = x + directions[d].first;
      const int32_t newY = y + directions[d].second;

      if (newX < 0 || newX >= rows || newY < 0 || newY >= cols) {
        continue;
      }

      if (grid[newX][newY] != '#') {
        pd = (d + 2) % 4;
        queue.push_back({newX, newY, dist + 1});
        points.push_back({newX, newY, dist + 1});
        break;
      }
    }
  }

  for (int i = 0; i < points.size(); i++) {
    const auto &[x1, y1, d1] = points[i];
    for (int j = i + 1; j < points.size(); j++) {
      const auto &[x2, y2, d2] = points[j];

      const uint16_t dx = std::abs(x1 - x2);
      const uint16_t dy = std::abs(y1 - y2);
      const uint16_t dist = dx + dy;

      if (dist > 20)
        continue;

      if (const uint16_t saved = std::abs(d1 - d2); saved >= dist + 100) {
        solution2++;
        if (dist <= 2) {
          solution1++;
        }
      }
    }
  }
}

int64_t Day20::part1(std::ifstream &file) {
  std::string line;
  std::vector<std::string> grid;

  while (std::getline(file, line)) {
    grid.push_back(line);
  }

  getPositions(grid);
  return solution1;
}

int64_t Day20::part2(std::ifstream &file) { return solution2; }
