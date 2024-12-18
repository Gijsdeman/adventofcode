#include <bitset>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>

#include "day09.h"

int64_t Day09::part1(std::ifstream &file) {
  uint64_t id = 0, current = 0, result = 0;

  std::string line;
  std::getline(file, line);
  std::vector blocks(line.size() * 9, -1);

  for (int i = 0; i < line.size(); i++) {
    const uint8_t blockSize = line[i] - '0';
    if (i % 2 == 0)
      std::fill_n(blocks.begin() + current, blockSize, id++);
    current += blockSize;
  }

  uint32_t left = 0, right = blocks.size() - 1;
  while (left < right) {
    while (left < right && blocks[left] != -1) {
      left++;
    }
    while (left < right && blocks[right] == -1) {
      right--;
    }
    std::swap(blocks[left++], blocks[right--]);
  }

  for (int i = 0; i < blocks.size(); i++) {
    if (blocks[i] != -1) {
      result += blocks[i] * i;
    }
  }

  return result;
}

int64_t Day09::part2(std::ifstream &file) {
  std::string line;
  std::getline(file, line);
  uint64_t current = 0, result = 0;

  std::vector<std::priority_queue<long, std::vector<long>, std::greater<long>>>
      spaces(10);
  std::vector<std::tuple<long, uint8_t, uint64_t>> characters;

  for (int i = 0; i < line.size(); i++) {
    const uint8_t blockSize = line[i] - '0';
    if (i % 2 == 0) {
      characters.push_back({current, blockSize, i / 2});
    } else {
      spaces[blockSize].push(current);
    }
    current += blockSize;
  }

  for (int i = characters.size() - 1; i >= 0; i--) {
    auto [blockIndex, blockSize, uid] = characters[i];

    int bestIndex = blockIndex;
    int bestSize = blockSize;
    for (int currentSpace = 0; currentSpace < 10; currentSpace++) {
      if (!spaces[currentSpace].empty()) {
        if (const auto spaceIndex = spaces[currentSpace].top();
            spaceIndex < bestIndex && blockSize <= currentSpace) {
          bestIndex = spaceIndex, bestSize = currentSpace;
        }
      }
    }

    // No spaces found, keep the block at same position
    if (spaces[bestSize].empty()) {
      for (int j = 0; j < blockSize; j++) {
        result += (blockIndex + j) * uid;
      }
      continue;
    }
    spaces[bestSize].pop();

    // Move the block to the best position
    for (int j = 0; j < blockSize; j++) {
      result += (bestIndex + j) * uid;
    }

    if (const auto extra = bestSize - blockSize; extra > 0) {
      spaces[extra].push(bestIndex + blockSize);
    }
  }

  return result;
}
