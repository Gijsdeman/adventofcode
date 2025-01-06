#include "day18.h"

#include <bitset>
#include <deque>
#include <fstream>
#include <iostream>

constexpr uint16_t DIM = 71;
constexpr int16_t SIZE = 1024;

const std::vector<std::pair<int32_t, int32_t>> Day18::directions = {
    {-1, 0}, {0, 1}, {1, 0}, {0, -1}};

std::pair<bool, uint16_t>
Day18::checkPossible(const std::vector<std::vector<char>> &grid) {
  std::deque<std::tuple<int16_t, int16_t, int16_t>> queue;
  std::bitset<DIM * DIM> visited;
  queue.push_back({0, 0, 0});

  bool possible = false;
  uint16_t distance = 0;
  while (!queue.empty()) {
    auto [x, y, dist] = queue.front();
    queue.pop_front();

    if (x == DIM - 1 && y == DIM - 1) {
      possible = true, distance = dist;
      break;
    }

    if (visited.test(x * DIM + y)) {
      continue;
    }
    visited.set(x * DIM + y);

    for (int d = 0; d < 4; d++) {
      int16_t newX = x + directions[d].first;
      int16_t newY = y + directions[d].second;

      if (newX >= 0 && newX < DIM && newY >= 0 && newY < DIM &&
          grid[newX][newY] != '#') {
        queue.push_back({newX, newY, dist + 1});
      }
    }
  }

  return {possible, distance};
}

int64_t Day18::part1(std::ifstream &file) {
  std::string line;
  std::vector grid(DIM, std::vector(DIM, '.'));

  uint16_t left, right;
  char comma;

  uint16_t i = 0;
  while (file >> left >> comma >> right) {
    if (i++ >= SIZE) {
      break;
    }
    grid[left][right] = '#';
  }

  auto [_, distance] = checkPossible(grid);
  return distance;
}

int64_t Day18::part2naive(std::ifstream &file) {
  std::string line;
  std::vector grid(DIM, std::vector(DIM, '.'));
  std::vector<std::pair<uint16_t, uint16_t>> locations;

  uint16_t left, right;
  char comma;

  while (file >> left >> comma >> right) {
    locations.push_back({left, right});
  }

  for (int i = 0; i < locations.size(); i++) {
    grid[locations[i].first][locations[i].second] = '#';
    if (i < DIM)
      continue;

    if (auto [possible, _] = checkPossible(grid); !possible) {
      std::cout << locations[i].first << ',' << locations[i].second
                << std::endl;
      break;
    }
  }
  return 0;
}

int64_t Day18::part2binary(std::ifstream &file) {
  std::string line;
  std::vector<std::pair<uint16_t, uint16_t>> locations;

  uint16_t left, right;
  char comma;

  while (file >> left >> comma >> right) {
    locations.push_back({left, right});
  }

  uint16_t low = 1024, high = locations.size();
  while (low <= high) {
    const uint64_t mid = low + (high - low) / 2;

    std::vector grid(DIM, std::vector(DIM, '.'));
    for (int i = 0; i < mid; i++) {
      grid[locations[i].first][locations[i].second] = '#';
    }

    if (auto [possible, _] = checkPossible(grid); possible) {
      low = mid + 1;
    } else {
      left = locations[mid - 1].first;
      right = locations[mid - 1].second;
      high = mid - 1;
    }
  }

  std::cout << left << ',' << right << std::endl;
  return 0;
}

int64_t Day18::part2(std::ifstream &file) {
  // return part2naive(file);
  return part2binary(file);
}
