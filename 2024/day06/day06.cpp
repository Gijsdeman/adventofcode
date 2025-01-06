#include "day06.h"

#include <bitset>
#include <fstream>

const std::vector<std::pair<int32_t, int32_t>> Day06::directions = {
    {-1, 0}, {0, 1}, {1, 0}, {0, -1}};

std::tuple<int32_t, int32_t, std::pair<int32_t, int32_t>>
Day06::getStartPos(const std::vector<std::string> &grid) {
  const short rows = grid.size();
  const short cols = grid[0].size();
  for (int i = 0; i < rows; i++) {
    for (int j = 0; j < cols; j++) {
      if (grid[i][j] == '^') {
        return {rows, cols, {i, j}};
      }
    }
  }
  return {0, 0, {0, 0}};
}

std::set<std::pair<int32_t, int32_t>>
Day06::getPositions(const std::vector<std::string> &grid) {
  auto [rows, cols, startPos] = getStartPos(grid);
  auto currentPos = startPos;
  int32_t currentDirection = 0;
  std::set visited{startPos};

  while (true) {
    const int32_t forwardPosX =
        currentPos.first + directions[currentDirection].first;
    const int32_t forwardPosY =
        currentPos.second + directions[currentDirection].second;

    if (forwardPosX < 0 || forwardPosX >= rows || forwardPosY < 0 ||
        forwardPosY >= cols)
      break;
    if (grid[forwardPosX][forwardPosY] == '#')
      currentDirection = (currentDirection + 1) % 4;

    currentPos = {currentPos.first + directions[currentDirection].first,
                  currentPos.second + directions[currentDirection].second};

    visited.insert(currentPos);
  }

  visited.erase(startPos);
  return visited;
}

int64_t Day06::part1(std::ifstream &file) {
  std::string line;
  std::vector<std::string> grid;

  while (std::getline(file, line)) {
    grid.push_back(line);
  }

  return getPositions(grid).size() + 1;
}

int64_t Day06::part2(std::ifstream &file) {
  std::string line;
  std::vector<std::string> grid;
  uint32_t result = 0;

  while (std::getline(file, line)) {
    grid.push_back(line);
  }

  auto [rows, cols, startPos] = getStartPos(grid);
  const std::set<std::pair<int32_t, int32_t>> obstaclePositions =
      getPositions(grid);
  std::bitset<1000000> visited;

  for (auto [oPosX, oPosY] : obstaclePositions) {
    auto [posX, posY] = startPos;
    int32_t currentDirection = 0;
    const bool changed = grid[oPosX][oPosY] != '#';
    grid[oPosX][oPosY] = '#';
    visited.reset();

    while (true) {
      int32_t forwardPosX = posX + directions[currentDirection].first;
      int32_t forwardPosY = posY + directions[currentDirection].second;

      if (forwardPosX < 0 || forwardPosX >= rows || forwardPosY < 0 ||
          forwardPosY >= cols)
        break;

      while (grid[forwardPosX][forwardPosY] == '#') {
        currentDirection = (currentDirection + 1) % 4;
        forwardPosX = posX + directions[currentDirection].first;
        forwardPosY = posY + directions[currentDirection].second;
      }

      posX += directions[currentDirection].first;
      posY += directions[currentDirection].second;

      const int32_t index = (posX * cols + posY) * 4 + currentDirection;
      if (visited.test(index)) {
        result++;
        break;
      }
      visited.set(index);
    }

    if (changed)
      grid[oPosX][oPosY] = '.';
  }

  return result;
}
