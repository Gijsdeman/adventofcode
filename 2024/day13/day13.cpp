#include "day13.h"

#include <fstream>
#include <regex>

long determinant(const std::pair<long, long> &left,
                 const std::pair<long, long> &right) {
  return left.first * right.second - left.second * right.first;
}

long cramer(const std::pair<long, long> &target, const std::pair<long, long> &A,
            const std::pair<long, long> &B) {
  const long detA = determinant(A, B);
  const long detA1 = determinant(target, B);
  const long detA2 = determinant(A, target);
  if (detA1 % detA == 0 && detA2 % detA == 0) {
    return 3 * detA1 / detA + detA2 / detA;
  }
  return 0;
}

void Day13::processPush(long &result, std::pair<long, long> &A,
                        std::pair<long, long> &B,
                        std::pair<long, long> &target) {
  if (A.first != -1 && B.first != -1 && target.first != -1) {
    result += cramer(target, A, B);
    A = B = target = {-1, -1};
  }
}

int64_t Day13::calculateTokens(std::ifstream &file, long addition) {
  std::string line;
  int64_t result = 0;
  const std::regex pattern("X[+=](\\d+), Y[+=](\\d+)");
  std::pair<long, long> A = {-1, -1}, B = {-1, -1}, target = {-1, -1};

  while (std::getline(file, line)) {
    const auto matches_begin =
        std::sregex_iterator(line.begin(), line.end(), pattern);
    auto matches_end = std::sregex_iterator();

    for (auto it = matches_begin; it != matches_end; ++it) {
      const auto &match = *it;
      const auto first = std::stoi(match.str(1));
      const auto second = std::stoi(match.str(2));

      if (A.first == -1)
        A = {first, second};
      else if (B.first == -1)
        B = {first, second};
      else
        target = {first + addition, second + addition};
    }
    processPush(result, A, B, target);
  }
  return result;
}

int64_t Day13::part1(std::ifstream &file) { return calculateTokens(file, 0); }

int64_t Day13::part2(std::ifstream &file) {
  return calculateTokens(file, 10000000000000);
}
