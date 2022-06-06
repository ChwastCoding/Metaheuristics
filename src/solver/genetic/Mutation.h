#ifndef __MUTATION_H__
#define __MUTATION_H__

#include <vector>

#include "../TwoOptSolver.h"

namespace mut {

/* Mutates permutation in place */
class Mutation {
  public:
  virtual void mutate(std::vector<int>& v) = 0;
};

class Insert : public Mutation {
  public:
  void mutate(std::vector<int>& v) override;
};

class Invert : public Mutation {
  public:
  void mutate(std::vector<int>& v) override;
};

class Swap : public Mutation {
  public:
  void mutate(std::vector<int>& v) override;
};

class TwoOptMutation : public Mutation {
 public:
  TwoOptMutation(std::shared_ptr<TSPInstance> instance, int steps);
  void mutate(std::vector<int>& v) override;

 private:
  int steps_;
  TwoOptSolver solver_;
};

} // namespace mut

#endif // __MUTATION_H__