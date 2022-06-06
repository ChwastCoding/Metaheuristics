#ifndef __CROSSOVER_H__
#define __CROSSOVER_H__

#include <vector>

class Crossover {
 public:
  typedef std::vector<int> solution;
  virtual void cross(solution& p1,
                     solution& p2,
                     solution& c1,
                     solution& c2) = 0;
};

class PMX : public Crossover {
 public:
  void cross(solution& p1, solution& p2, solution& c1, solution& c2) override;
};

class Order1 : public Crossover {
 public:
  void cross(solution& p1, solution& p2, solution& c1, solution& c2) override;
};


#endif  // __CROSSOVER_H__