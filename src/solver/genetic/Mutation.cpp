#include "Mutation.h"

#include "../../util.h"

#include <algorithm>

namespace mut {

void Insert::mutate(std::vector<int>& v)
{
  int pos_to_remove = util::random(v.size());
  int pos_to_insert = util::random(v.size() - 1);
  int t = v[pos_to_remove];
  v.erase(v.begin() + pos_to_remove);
  v.insert(v.begin() + pos_to_insert, t);
}

void rotation(std::vector<int>& s, int a, int b) {
    int c;
    do {
        std::swap(s[a], s[b]);
        c = a;
        if (++a == s.size()) a = 0;
        if (--b == -1) b = s.size() - 1;
    } while (c != b && b != a);
}

void Invert::mutate(std::vector<int>& v)
{
  int a = util::random(v.size());
  int b = util::random(v.size()); 
  if (a > b) {
    rotation(v, a, b);
  } else if (a < b) {
    std::reverse(v.begin() + a, v.begin() + b + 1);
  }
}

void Swap::mutate(std::vector<int>& v)
{
  int a = util::random(v.size());
  int b = util::random(v.size()); 
  if (a != b) {
    std::swap(v[a], v[b]);
  }
}

TwoOptMutation::TwoOptMutation(std::shared_ptr<TSPInstance> instance, int steps)
    : solver_(instance), steps_(steps) {}

void TwoOptMutation::mutate(std::vector<int>& v)
{
  solver_.setSolution(v);
  for (int i = 0; i < steps_; i ++ ) {
    solver_.step();
  }
  v = solver_.getSolution();
}


} // namespace mut