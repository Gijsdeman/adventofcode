#include "day14.h"

#include <fstream>
#include <regex>

constexpr uint32_t WIDTH = 101;
constexpr uint32_t HEIGHT = 103;
constexpr uint32_t MIDX = (WIDTH - 1) / 2;
constexpr uint32_t MIDY = (HEIGHT - 1) / 2;

void Day14::parseInput(std::ifstream &file,
                       std::vector<std::pair<int32_t, int32_t>> &points,
                       std::vector<std::pair<int32_t, int32_t>> &vectors) {
  std::string line;
  std::vector<std::string> grid;

  const std::regex pattern("p=(\\d+),(\\d+) v=(-?\\d+),(-?\\d+)");

  while (std::getline(file, line)) {
    const auto matches_begin =
        std::sregex_iterator(line.begin(), line.end(), pattern);
    const auto matches_end = std::sregex_iterator();

    for (std::sregex_iterator i = matches_begin; i != matches_end; ++i) {
      points.push_back({std::stoi(i->str(1)), std::stoi(i->str(2))});
      vectors.push_back({std::stoi(i->str(3)), std::stoi(i->str(4))});
    }
  }
}

uint32_t Day14::wrap(const int32_t value, const int32_t mod) {
  return (value % mod + mod) % mod;
}

int64_t Day14::part1(std::ifstream &file) {
  std::vector<std::pair<int32_t, int32_t>> points;
  std::vector<std::pair<int32_t, int32_t>> vectors;
  parseInput(file, points, vectors);

  for (int i = 0; i < 100; i++) {
    for (int j = 0; j < points.size(); j++) {
      points[j].first = wrap(points[j].first + vectors[j].first, WIDTH);
      points[j].second = wrap(points[j].second + vectors[j].second, HEIGHT);
    }
  }

  uint32_t tl = 0, tr = 0, bl = 0, br = 0;
  for (const auto &[x, y] : points) {
    if (x < MIDX && y < MIDY) {
      tl++;
    }
    if (x < MIDX && y > MIDY) {
      bl++;
    }
    if (x > MIDX && y < MIDY) {
      tr++;
    }
    if (x > MIDX && y > MIDY) {
      br++;
    }
  }

  return tl * tr * bl * br;
}

// For some reason, solution is when all points are unique
int64_t Day14::part2(std::ifstream &file) {
  std::vector<std::pair<int32_t, int32_t>> points;
  std::vector<std::pair<int32_t, int32_t>> vectors;
  parseInput(file, points, vectors);

  uint64_t result = 0;
  std::vector visited(WIDTH * HEIGHT, -1);

  while (true) {
    result++;

    for (int j = 0; j < points.size(); j++) {
      points[j].first = wrap(points[j].first + vectors[j].first, WIDTH);
      points[j].second = wrap(points[j].second + vectors[j].second, HEIGHT);
    }

    bool allUnique = true;
    for (auto &[x, y] : points) {
      if (visited[x * WIDTH + y] == result) {
        allUnique = false;
        break;
      }
      visited[x * WIDTH + y] = result;
    }

    if (allUnique) {
      break;
    }
  }
  return result;
}
