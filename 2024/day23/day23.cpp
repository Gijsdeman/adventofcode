#include "day23.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <ranges>

void Day23::BronKerbosch(
    const std::set<std::string> &R, std::set<std::string> &P,
    std::set<std::string> &X,
    const std::unordered_map<std::string, std::set<std::string>> &adj,
    std::vector<std::string> &clique) {

  if (P.empty() && X.empty()) {
    if (R.size() > clique.size()) {
      clique = std::vector(R.begin(), R.end());
    }
    return;
  }

  std::string pivot;
  if (!P.empty()) {
    pivot = *P.begin();
  } else if (!X.empty()) {
    pivot = *X.begin();
  }

  std::set<std::string> neighbors = adj.at(pivot);
  std::set<std::string> candidates;
  std::ranges::set_difference(P, neighbors,
                              std::inserter(candidates, candidates.begin()));

  for (const auto &node : candidates) {
    std::set<std::string> Rn = R;
    Rn.insert(node);

    std::set<std::string> Pn;
    std::set<std::string> Xn;

    for (const auto &neighbor : adj.at(node)) {
      if (P.contains(neighbor)) {
        Pn.insert(neighbor);
      }
      if (X.contains(neighbor)) {
        Xn.insert(neighbor);
      }
    }

    BronKerbosch(Rn, Pn, Xn, adj, clique);

    P.erase(node);
    X.insert(node);
  }
}

int64_t Day23::part1(std::ifstream &file) {
  std::string line;
  std::unordered_map<std::string, std::set<std::string>> adj;

  while (std::getline(file, line)) {
    const auto pos = line.find('-');
    auto first = line.substr(0, pos);
    auto second = line.substr(pos + 1);

    adj[first].insert(second);
    adj[second].insert(first);
  }

  uint16_t result = 0;
  for (const auto &[key, adjSet] : adj) {
    std::vector adjVec(adjSet.begin(), adjSet.end());
    for (int i = 0; i < adjVec.size(); i++) {
      for (int j = i + 1; j < adjVec.size(); j++) {
        const std::string &ni = adjVec[i];
        const std::string &nj = adjVec[j];
        if (adj[ni].contains(nj)) {
          if (key.starts_with("t") || nj.starts_with("t") ||
              ni.starts_with("t")) {
            result++;
          }
        }
      }
    }
  }
  return result / 3;
}

int64_t Day23::part2(std::ifstream &file) {
  std::string line;
  std::unordered_map<std::string, std::set<std::string>> adj;

  while (std::getline(file, line)) {
    const auto pos = line.find('-');
    auto first = line.substr(0, pos);
    auto second = line.substr(pos + 1);

    adj[first].insert(second);
    adj[second].insert(first);
  }

  std::set<std::string> P;
  std::set<std::string> X;
  const std::set<std::string> R;
  std::vector<std::string> C;

  for (const auto &key : adj | std::views::keys) {
    P.insert(key);
  }

  BronKerbosch(R, P, X, adj, C);

  std::ranges::sort(C);
  for (int i = 0; i < C.size(); i++) {
    std::cout << C[i];
    if (i != C.size() - 1) {
      std::cout << ",";
    }
  }
  std::cout << std::endl;

  return 0;
}
