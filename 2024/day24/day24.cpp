#include "day24.h"

#include <fstream>
#include <iostream>
#include <ranges>
#include <sstream>

void Day24::parseInput(std::ifstream &file,
                       std::queue<std::vector<std::string>> &toCheck,
                       std::map<std::string, bool> &gates) {
  std::string line;

  while (std::getline(file, line) && !line.empty()) {
    const auto gate = line.substr(0, 3);
    const auto val = line.substr(5);
    gates[gate] = val == "1";
  }

  while (std::getline(file, line) && !line.empty()) {
    std::istringstream stream(line);
    std::string parts;
    std::vector<std::string> part;
    while (std::getline(stream, parts, ' ')) {
      part.push_back(parts);
    }
    toCheck.push(part);
  }
}

bool Day24::computeGate(const std::string &op, const bool a, const bool b) {
  if (op == "AND") {
    return a && b;
  }
  if (op == "OR") {
    return a || b;
  }
  return a ^ b;
}

bool Day24::wrongOperator(const std::string &op, const std::string &left,
                          const std::string &right) {
  return (op == "AND" || op == "OR" ||
          (op == "XOR" && ((left.starts_with("x") && right.starts_with("y")) ||
                           (left.starts_with("y") && right.starts_with("x")))));
}

void Day24::checkOperatorCombination(const std::set<std::string> &set,
                                     const std::string &left,
                                     const std::string &right,
                                     std::set<std::string> &wrong) {
  if (set.contains(left))
    wrong.insert(left);
  if (set.contains(right))
    wrong.insert(right);
}

void Day24::getZ(std::queue<std::vector<std::string>> &toCheck,
                 std::map<std::string, bool> &gates,
                 std::map<std::string, bool> &z) {
  while (!toCheck.empty()) {
    const auto current = toCheck.front();
    toCheck.pop();

    const auto &gate1 = current[0];
    const auto &op = current[1];
    const auto &gate2 = current[2];
    const auto &target = current[4];

    if (!gates.contains(gate1) || !gates.contains(gate2)) {
      toCheck.push(current);
      continue;
    }

    const bool result = computeGate(op, gates[gate1], gates[gate2]);
    if (target.starts_with("z")) {
      gates[target] = result;
      z[target] = result;
    } else {
      gates[target] = result;
    }
  }
}

int64_t Day24::part1(std::ifstream &file) {
  std::map<std::string, bool> gates;
  std::map<std::string, bool> z;
  std::queue<std::vector<std::string>> toCheck;

  parseInput(file, toCheck, gates);
  getZ(toCheck, gates, z);

  int64_t number = 0;
  int index = 0;
  for (auto const &value : std::views::values(z)) {
    number |= static_cast<int64_t>(value) << index++;
  }

  return number;
}

int64_t Day24::part2(std::ifstream &file) {
  std::map<std::string, bool> gates;
  std::map<std::string, bool> z;
  std::queue<std::vector<std::string>> toCheck;

  parseInput(file, toCheck, gates);

  std::set<std::string> Mn;
  std::set<std::string> Nn;
  std::set<std::string> Rn;
  std::set<std::string> wrong;

  // Xn XOR Yn > Mn
  // Xn AND Yn > Nn
  // Cn-1 AND Mn > Rn
  // Cn-1 XOR Mn > Zn
  // Rn OR Nn > Cn
  while (wrong.size() < 8) {
    const auto part = toCheck.front();
    toCheck.pop();

    // Check if Z is in wrong position
    if (part[4].starts_with("z") && part[4] != "z00" && part[4] != "z45" &&
        wrongOperator(part[1], part[0], part[2])) {
      wrong.insert(part[4]);
    }

    if (part[1] == "AND") {
      if (part[0] == "x00" || part[2] == "x00")
        continue;

      // Check if Rn of Nn
      if ((part[0].starts_with("x") && part[2].starts_with("y")) ||
          (part[2].starts_with("x") && part[0].starts_with("y"))) {
        Nn.insert(part[4]);
      } else if (!part[0].starts_with("x") && !part[2].starts_with("y") &&
                 !part[2].starts_with("x") && !part[0].starts_with("y")) {
        Rn.insert(part[4]);
      }

      // Check if Rn or Nn appears in combination with wrong operator
      checkOperatorCombination(Rn, part[0], part[2], wrong);
      checkOperatorCombination(Nn, part[0], part[2], wrong);
    }

    if (part[1] == "XOR") {
      // Check if Mn
      if ((part[0].starts_with("x") && part[2].starts_with("y")) ||
          (part[2].starts_with("x") && part[0].starts_with("y"))) {
        Mn.insert(part[4]);
      }

      // Validate if Zn
      if (!part[0].starts_with("x") && !part[0].starts_with("y") &&
          !part[2].starts_with("x") && !part[2].starts_with("y") &&
          !part[4].starts_with("z")) {
        wrong.insert(part[4]);
      }

      // Check if Rn or Nn appears in combination with wrong operator
      checkOperatorCombination(Rn, part[0], part[2], wrong);
      checkOperatorCombination(Nn, part[0], part[2], wrong);
    }

    if (part[1] == "OR") {
      // Check if Mn appears in combination with wrong operator
      checkOperatorCombination(Mn, part[0], part[2], wrong);
    }
    toCheck.push(part);
  }

  for (auto it = wrong.begin(); it != wrong.end(); ++it) {
    if (it != wrong.begin()) {
      std::cout << ",";
    }
    std::cout << *it;
  }
  std::cout << std::endl;
  return 0;
}
