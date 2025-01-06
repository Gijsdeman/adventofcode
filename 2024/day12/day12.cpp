#include "day12.h"

#include <bitset>
#include <deque>
#include <fstream>
#include <ranges>
#include <sstream>

const std::vector<std::pair<int8_t, int8_t>> Day12::directions = {
    {-1, 0}, {0, 1}, {1, 0}, {0, -1}};

std::vector<std::vector<char>> createGrid(std::ifstream &file) {
  std::string line;
  std::vector<std::vector<char>> grid;
  uint8_t columns = INT8_MAX;

  grid.push_back({'0'});
  while (std::getline(file, line)) {
    if (columns == INT8_MAX) {
      columns = line.size();
    }
    std::istringstream lineStream(line);
    char number;

    std::vector<char> row;
    row.push_back('0');
    while (lineStream >> number) {
      row.push_back(number);
    }
    row.push_back('0');
    grid.push_back(row);
  }
  const std::vector padding(columns + 2, '0');
  grid[0] = padding;
  grid.push_back(padding);

  return grid;
}

int64_t Day12::part1(std::ifstream &file) {
  const auto grid = createGrid(file);
  const uint32_t columns = grid[0].size();
  uint32_t result = 0;

  std::bitset<25000> visited;
  std::deque<std::pair<uint8_t, uint8_t>> queue;

  for (int i = 1; i < grid.size() - 1; i++) {
    for (int j = 1; j < grid[0].size() - 1; j++) {
      std::pair startPos = {i, j};
      if (visited.test(i * columns + j)) {
        continue;
      }

      queue.clear();
      queue.push_back(startPos);

      uint16_t area = 0, perimeter = 0;
      while (!queue.empty()) {
        auto [currX, currY] = queue.front();
        queue.pop_front();

        const int32_t currentIndex = currX * columns + currY;
        if (visited.test(currentIndex))
          continue;
        visited.set(currentIndex);
        area++;

        for (int d = 0; d < 4; d++) {
          if (std::pair<uint8_t, uint8_t> newPosition =
                  {currX + directions[d].first, currY + directions[d].second};
              grid[newPosition.first][newPosition.second] == grid[i][j]) {
            queue.push_back(newPosition);
          } else {
            perimeter++;
          }
        }
      }
      result += area * perimeter;
    }
  }
  return result;
}

int64_t Day12::part2(std::ifstream &file) {
  const auto grid = createGrid(file);
  const uint32_t columns = grid[0].size();
  uint32_t result = 0;

  std::bitset<25000> visited;
  std::deque<std::pair<int32_t, int32_t>> queue;
  perimeterMap perimeter;
  std::bitset<25000> visitedPerimeter;

  for (int i = 1; i < grid.size() - 1; i++) {
    for (int j = 1; j < grid[0].size() - 1; j++) {
      perimeter.clear();
      std::pair startPos = {i, j};
      if (visited.test(i * columns + j)) {
        continue;
      }

      queue.clear();
      queue.push_back(startPos);

      int area = 0, sides = 0;
      while (!queue.empty()) {
        auto [currX, currY] = queue.front();
        queue.pop_front();

        const int32_t currentIndex = currX * columns + currY;
        if (visited.test(currentIndex))
          continue;
        visited.set(currentIndex);
        area++;

        for (int d = 0; d < 4; d++) {
          if (std::pair<uint8_t, uint8_t> newPosition =
                  {currX + directions[d].first, currY + directions[d].second};
              grid[newPosition.first][newPosition.second] == grid[i][j]) {
            queue.push_back(newPosition);
          } else {
            perimeter[directions[d].first * 2 + directions[d].second].insert(
                {currX, currY});
          }
        }
      }

      // Any perimeter has same direction and is connected
      // We run yet another BFS restricted to the perimeter
      for (auto perimeterPositions : std::views::values(perimeter)) {
        visitedPerimeter.reset();

        for (auto perimeterPos : perimeterPositions) {
          // Unseen position is part of perimeter not connected, so it is a side
          if (!visitedPerimeter.test(perimeterPos.first * columns +
                                     perimeterPos.second)) {
            sides += 1;
            queue.clear();
            queue.push_back(perimeterPos);

            while (!queue.empty()) {
              auto [currX, currY] = queue.front();
              queue.pop_front();

              if (visitedPerimeter.test(currX * columns + currY)) {
                continue;
              }
              visitedPerimeter.set(currX * columns + currY);

              for (int d = 0; d < 4; d++) {
                if (const std::pair newPos = {currX + directions[d].first,
                                              currY + directions[d].second};
                    perimeterPositions.contains(newPos)) {
                  queue.push_back(newPos);
                }
              }
            }
          }
        }
      }
      result += area * sides;
    }
  }
  return result;
}
