#include "Crossover.h"

#include <algorithm>
#include "../../util.h"

#include <iostream>

// assume c is filled with -1
void createChildPMX(Crossover::solution& p1,
                    Crossover::solution& p2,
                    Crossover::solution& c,
                    int p,
                    int q) {
  std::copy(p1.begin() + p, p1.begin() + q, c.begin() + p);

  for (int i = p; i < q; i++) {
    int not_copied = p2[i];
    auto found = std::find(c.begin(), c.end(), not_copied);

    if (found == c.end()) {
      int position = i;
      while (true) {
        int V = p1[position];
        int V_position = std::find(p2.begin(), p2.end(), V) - p2.begin();
        position = V_position;
        if (position < p || position >= q) {
          break;
        }
      }
      c[position] = not_copied;
    }
  }

  for (int i = 0; i < c.size(); i++) {
    if (c[i] == -1)
      c[i] = p2[i];
  }
}

void PMX::cross(solution& p1, solution& p2, solution& c1, solution& c2) {
  int a = util::random(1, p1.size() - 1);
  int b = util::random(1, p1.size() - 1);
  int p = std::min(a, b);
  int q = std::max(a, b);

  createChildPMX(p1, p2, c1, p, q);
  createChildPMX(p2, p1, c2, p, q);
}

bool checkMutation(const std::vector<int>& v) {
  std::vector<int> checks(v.size(), 0);
  if (v.end() - v.begin() != v.size()) {
    std::cout << "Failed size check" << std::endl;
    return false;
  }
  for (auto e : v) {
    checks[e] ++;
  }
  bool res = true;
  for (int i = 0; i < v.size(); i++) {
    if (checks[i] != 1){
      std::cout << "chescks[" << i << "] = " << checks[i] << std::endl;
      res = false;
    }
  }
  return res;
}

bool smallCheck(std::vector<int>& c) {
  std::vector<int> checks(c.size(), 0);
  for (auto t : c) {
    if (t > 0) {
      checks[t] ++;
    }
  } 
  bool res = true;
  for (int i = 0; i < c.size(); i++) {
    if (checks[i] > 1){
      std::cout << "chescks[" << i << "] = " << checks[i] << std::endl;
      res = false;
    }
  }
  return res;
}

void createChildOrder1(Crossover::solution& p1,
                       Crossover::solution& p2,
                       Crossover::solution& c,
                       int p,
                       int q) {
  std::copy(p1.begin() + p, p1.begin() + q, c.begin() + p);

  for (int i = 0, j = 0; i < c.size(); i++) {
    if (std::find(c.begin(), c.end(), p2[i]) == c.end()) {
      c[j] = p2[i];
      if (++j == p)
        j = q;
    }
  }
}

void Order1::cross(solution& p1, solution& p2, solution& c1, solution& c2) {
  int a = util::random(1, p1.size() - 1);
  int b = util::random(1, p1.size() - 1);
  int p = std::min(a, b);
  int q = std::max(a, b);

  createChildOrder1(p1, p2, c1, p, q);
  createChildOrder1(p2, p1, c2, p, q);
}