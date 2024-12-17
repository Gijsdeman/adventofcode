#include <bitset>
#include <boost/container/flat_set.hpp>
#include <complex>
#include <fstream>
#include <iostream>
#include <sstream>

#include "day17.h"

void Day17::parseInput(std::ifstream &file, std::vector<uint64_t> &registers,
                       std::vector<uint16_t> &operations) {
  std::string line;
  for (int i = 0; i < 3 && std::getline(file, line); i++) {
    registers[i] = std::stoi(line.substr(12));
  }

  std::getline(file, line);
  std::getline(file, line);
  line = line.substr(9);

  std::istringstream iss(line);
  std::string number;
  while (getline(iss, number, ',')) {
    operations.push_back(std::stoi(number));
  }
}

std::vector<uint16_t>
Day17::executeProgram(std::vector<uint64_t> &registers,
                      const std::vector<uint16_t> &operations) {
  std::vector<uint16_t> result;
  result.reserve(10);

  auto combo = [&registers](const uint16_t operand) -> uint64_t {
    if (operand < 4) {
      return operand;
    }
    return registers[operand - 4];
  };

  int pointer = 0;

  while (pointer < operations.size()) {
    const int operand = operations[pointer + 1];

    switch (operations[pointer]) {
    case 0:
      registers[0] >>= combo(operand);
      break;
    case 1:
      registers[1] ^= operand;
      break;
    case 2:
      registers[1] = combo(operand) & 7;
      break;
    case 3:
      if (registers[0] != 0) {
        pointer = operand;
        continue;
      }
      break;
    case 4:
      registers[1] ^= registers[2];
      break;
    case 5:
      result.push_back(combo(operand) & 7);
      break;
    case 6:
      registers[1] = registers[0] >> combo(operand);
      break;
    case 7:
      registers[2] = registers[0] >> combo(operand);
      break;
    default:
      break;
    }
    pointer += 2;
  }

  return result;
}

uint64_t Day17::depthSearch(std::vector<uint16_t> &operations,
                            const uint64_t currentValue,
                            const uint16_t pointer) {
  std::vector<uint64_t> registers = {0, 0, 0};
  for (int candidate = 0; candidate < 8; candidate++) {
    const uint64_t newValue = currentValue * 8 + candidate;
    registers[0] = newValue;

    auto result = executeProgram(registers, operations);

    if (std::vector currentProgram(operations.begin() + pointer,
                                   operations.end());
        result == currentProgram) {
      if (pointer == 0) {
        return newValue;
      }
      if (const uint64_t res = depthSearch(operations, newValue, pointer - 1);
          res < UINT64_MAX) {
        return res;
      }
    }
  }
  return UINT64_MAX;
}

int64_t Day17::part1(std::ifstream &file) {
  std::vector<uint64_t> registers(3);
  std::vector<uint16_t> operations;

  parseInput(file, registers, operations);
  const auto result = executeProgram(registers, operations);

  for (int i = 0; i < result.size(); i++) {
    std::cout << result[i];
    if (i != result.size() - 1) {
      std::cout << ',';
    }
  }
  std::cout << std::endl;
  return 0;
}

int64_t Day17::part2(std::ifstream &file) {
  std::string line;
  std::vector<std::string> grid;

  std::vector<uint64_t> registers(3);
  std::vector<uint16_t> operations;

  parseInput(file, registers, operations);
  return depthSearch(operations, 0, operations.size() - 1);
}
