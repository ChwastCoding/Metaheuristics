#ifndef __GENETIC_H__
#define __GENETIC_H__

#include "../Solver.h"
#include "Crossover.h"
#include "Mutation.h"

class Genetic : public Solver {
public:
  /* Both under crossover for TSP section 4.1.1 and 4.1.3 */
  enum Operator {
    PMX,
    Order1
  };
  enum InitialSolution {
    Random, 
    // Starts with random permutations
    TwoOpt, 
    /* Creates random permutations and then 
    performs  two_opt_initial_step_count of TwoOptSolver 
    steps on each of them, if two_opt_initial_step_count = -1
    2Opt steps untill no farther optimalization is possible*/
  };
  enum MutationType {
    Insert,
    Invert,
    Swap,
    /* Modyfie solution like in tabu search */
    TwoOptM
    /* Performs two_opt_step_count_ stesps of TwoOptSolver on a solution*/
  };
  enum SelectionMethod {
    RandomSelection, /* Selects parents at random */
    Probabilistic /* Selects parents with probability 1 / f(x) */
  };

  enum ReductionMode {
    Best, /* saves the strongest individuals */
    ProbabilisticRed /* Selects based on quality of soluction... 
    but not to well */
  };

  /* number_of_parents and population_size must be even */
  Genetic(std::shared_ptr<TSPInstance> instance,
          Operator op,
          InitialSolution in_sol,
          MutationType muration,
          SelectionMethod selection_method,
          float mutation_chance,
          int population_size,
          int number_of_parents,
          int two_opt_step_count,
          int two_opt_initial_step_count);

  // always return true, user needs to implement stop logic
  bool step() override;
  int calculateObjectiveFunction() override;
  // TSPInstance::solution getSolution() override;

protected:
  typedef std::pair<TSPInstance::solution, int> pair;
  
  /* reducces population to population_size_ and sets 
  optimal solution */
  void reducePopulation();
  // gets parenst with probability 1 / f(x)
  std::vector<int> getInvertProbabilisticParents();
  // gets solution with liner probability
  std::vector<int> getProbabilisticCandidates(int x);
  pair getTwoOptInitialSolution(TwoOptSolver* solver);
  void initializeTwoOptSolutions();
  // void crossAndMutate();

  Operator operator_;
  InitialSolution initial_solution_;
  SelectionMethod selection_method_;
  ReductionMode reduction_mode_ = ReductionMode::Best;
  
  std::shared_ptr<Crossover> crossover_operator_;
  std::shared_ptr<mut::Mutation> mutation_;

  std::vector<pair> population_;
  int population_size_;
  int best_solution_index_;
  int optimal_solution_cost_; 
  int number_of_parents_;
  int two_opt_step_count_;
  int two_opt_initial_step_count_;
  float mutation_chance_;

};

#endif // __GENETIC_H__