#include "day15.h"

#include <fstream>
#include <regex>

const std::vector<std::pair<int32_t, int32_t>> directions = {
    {-1, 0}, {0, 1}, {1, 0}, {0, -1}};

void Day15::parseInput(std::ifstream &file, std::vector<std::string> &grid,
                       std::pair<uint32_t, uint32_t> &currentPos,
                       const bool part2) {
  std::string line;
  int row = 0;
  while (std::getline(file, line) && !line.empty()) {
    if (part2) {
      std::string newLine = "";
      newLine.reserve(line.size() * 2);

      for (const char c : line) {
        switch (c) {
        case '#':
          newLine += "##";
          break;
        case '@':
          newLine += "@.";
          break;
        case '.':
          newLine += "..";
          break;
        case 'O':
          newLine += "[]";
          break;
        default:
          break;
        }
      }
      line = std::move(newLine);
    }

    if (auto pos = line.find('@'); pos != std::string::npos) {
      currentPos = {row, pos};
      line[pos] = '.';
    }

    grid.push_back(line);
    ++row;
  }
}

void Day15::walk(std::ifstream &file, std::vector<std::string> &grid,
                 std::pair<uint32_t, uint32_t> &currentPos) {
  std::string line;
  std::map<char, std::pair<int32_t, int32_t>> directions = {
      {'<', {0, -1}}, {'>', {0, 1}}, {'^', {-1, 0}}, {'v', {1, 0}}};
  auto queue = std::deque<std::pair<int32_t, int32_t>>();

  while (std::getline(file, line)) {
    for (const auto c : line) {
      auto [dx, dy] = directions[c];
      int nx = currentPos.first + dx;
      int ny = currentPos.second + dy;

      char cell = grid[nx][ny];
      if (cell == '.') {
        currentPos = {nx, ny};
        continue;
      }

      if (cell == '#') {
        continue;
      }

      if (cell == '[' || cell == ']' || cell == 'O') {
        queue.clear();
        queue.emplace_back(currentPos);
        std::vector<std::pair<int32_t, int32_t>> pushed;
        bool isValid = true;

        while (!queue.empty()) {
          auto [ox, oy] = queue.front();
          queue.pop_front();

          // In case of double block, we need to check if already pushed
          if (std::ranges::find(pushed, std::make_pair(ox, oy)) !=
              pushed.end()) {
            continue;
          }
          pushed.emplace_back(ox, oy);

          uint32_t nox = ox + dx;
          uint32_t noy = oy + dy;

          const char pushedCell = grid[nox][noy];
          if (pushedCell == '#') {
            isValid = false;
            break;
          }

          if (pushedCell == 'O' || pushedCell == '[' || pushedCell == ']') {
            queue.emplace_back(nox, noy);
            if (pushedCell == '[') {
              queue.emplace_back(nox, noy + 1);
            } else if (pushedCell == ']') {
              queue.emplace_back(nox, noy - 1);
            }
          }
        }

        if (!isValid) {
          continue;
        }

        for (auto itt = pushed.rbegin(); itt != pushed.rend(); ++itt) {
          auto [cx, cy] = *itt;
          grid[cx + dx][cy + dy] = grid[cx][cy];
          grid[cx][cy] = '.';
        }
        currentPos = {nx, ny};
      }
    }
  }
}

int32_t Day15::getScore(const std::vector<std::string> &grid) {
  uint32_t result = 0;
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[0].size(); j++) {
      if (grid[i][j] == 'O' || grid[i][j] == '[') {
        result += 100 * i + j;
      }
    }
  }
  return result;
}

int64_t Day15::part1(std::ifstream &file) {
  std::string line;
  std::vector<std::string> grid;

  std::pair<uint32_t, uint32_t> currentPos = {0, 0};
  parseInput(file, grid, currentPos, false);
  walk(file, grid, currentPos);
  return getScore(grid);
}

int64_t Day15::part2(std::ifstream &file) {
  std::string line;
  std::vector<std::string> grid;

  std::pair<uint32_t, uint32_t> currentPos = {0, 0};
  parseInput(file, grid, currentPos, true);
  walk(file, grid, currentPos);
  return getScore(grid);
}
