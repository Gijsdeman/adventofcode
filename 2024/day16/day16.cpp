#include "day16.h"

#include <fstream>
#include <iostream>
#include <queue>
#include <regex>
#include <set>

const std::vector<std::pair<int32_t, int32_t>> directions = {
    {-1, 0}, {0, 1}, {1, 0}, {0, -1}};

std::tuple<int32_t, int32_t, std::pair<int32_t, int32_t>,
           std::pair<int32_t, int32_t>>
getPositions(const std::vector<std::string> &grid) {
  const uint8_t rows = grid.size();
  const uint8_t cols = grid[0].size();
  std::pair start = {0, 0};
  std::pair end = {0, 0};
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (grid[i][j] == 'S') {
        start = {i, j};
      } else if (grid[i][j] == 'E') {
        end = {i, j};
      }
    }
  }
  return {rows, cols, start, end};
}

int32_t
Day16::Dijkstra(const std::vector<std::string> &grid,
                std::vector<std::vector<std::vector<int32_t>>> &distance,
                const bool reverse) {
  auto [rows, cols, start, end] = getPositions(grid);

  auto compare = [](const std::pair<int, Point> &a,
                    const std::pair<int, Point> &b) {
    return a.first > b.first;
  };
  std::priority_queue<std::pair<int, Point>, std::vector<std::pair<int, Point>>,
                      decltype(compare)>
      queue(compare);

  if (reverse) {
    for (int d = 0; d < 4; d++) {
      distance[end.first][end.second][d] = 0;
      queue.push({0, {end.first, end.second, d}});
    }
  } else {
    distance[start.first][start.second][1] = 0;
    queue.push({0, {start.first, start.second, 1}});
  }

  int32_t result = INT32_MAX;

  while (!queue.empty()) {
    const auto [cost, p] = queue.top();
    queue.pop();

    if (!reverse && p.x == end.first && p.y == end.second) {
      result = std::min(result, cost);
      continue;
    }

    uint8_t newD = (p.d + 1) % 4;
    if (cost + 1000 < distance[p.x][p.y][newD]) {
      distance[p.x][p.y][newD] = cost + 1000;
      queue.push({cost + 1000, {p.x, p.y, newD}});
    }

    newD = (p.d + 3) % 4;
    if (cost + 1000 < distance[p.x][p.y][newD]) {
      distance[p.x][p.y][newD] = cost + 1000;
      queue.push({cost + 1000, {p.x, p.y, newD}});
    }

    auto &[dx, dy] = directions[reverse ? (p.d + 2) % 4 : p.d];
    const int16_t newX = p.x + dx;
    const int16_t newY = p.y + dy;

    if (newX >= 0 && newX < rows && newY >= 0 && newY < cols &&
        grid[newX][newY] != '#') {
      if (cost + 1 < distance[newX][newY][p.d]) {
        distance[newX][newY][p.d] = cost + 1;
        queue.push({cost + 1, {newX, newY, p.d}});
      }
    }
  }

  return result;
}

int64_t Day16::part1(std::ifstream &file) {
  std::string line;
  std::vector<std::string> grid;
  const std::regex pattern("p=(\\d+),(\\d+) v=(-?\\d+),(-?\\d+)");
  while (std::getline(file, line)) {
    grid.push_back(line);
  }

  const auto rows = grid.size();
  const auto cols = grid[0].size();
  std::vector distance(rows, std::vector(cols, std::vector(4, INT32_MAX)));
  return Dijkstra(grid, distance, false);
}

int64_t Day16::part2(std::ifstream &file) {
  std::string line;
  std::vector<std::string> grid;
  const std::regex pattern("p=(\\d+),(\\d+) v=(-?\\d+),(-?\\d+)");
  while (std::getline(file, line)) {
    grid.push_back(line);
  }

  const auto rows = grid.size();
  const auto cols = grid[0].size();
  std::vector distance(rows, std::vector(cols, std::vector(4, INT32_MAX)));
  std::vector rdistance(rows, std::vector(cols, std::vector(4, INT32_MAX)));

  const int32_t opt = Dijkstra(grid, distance, false);
  Dijkstra(grid, rdistance, true);

  std::set<std::pair<int, int>> visited;
  for (int r = 0; r < rows; r++) {
    for (int c = 0; c < cols; c++) {
      for (int d = 0; d < 4; d++) {
        if (rdistance[r][c][d] < INT32_MAX && distance[r][c][d] < INT32_MAX) {
          if (rdistance[r][c][d] + distance[r][c][d] <= opt) {
            visited.insert({r, c});
          }
        }
      }
    }
  }

  return visited.size();
}
