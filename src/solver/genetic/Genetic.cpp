#include "Genetic.h"
#include "../../util.h"

#include <algorithm>
#include <numeric>
#include <memory>
#include <iostream>
#include <random>

// makes check if mutation were correct
// #define CHECK_MUTATION

std::vector<int> random_permutation(int size) {
  std::vector<int> v(size);
  std::iota(v.begin(), v.end(), 0);
  std::random_shuffle(v.begin(), v.end());

  return v;
}

Genetic::Genetic(std::shared_ptr<TSPInstance> instance,
                 Operator op,
                 InitialSolution in_sol,
                 MutationType mutation,
                 SelectionMethod selection_method,
                 float muation_chance,
                 int population_size,
                 int number_of_parents,
                 int two_opt_step_count,
                 int two_opt_initial_step_count_)
    : Solver(instance),
      operator_(op),
      initial_solution_(in_sol),
      selection_method_(selection_method),
      population_(population_size),
      population_size_(population_size),
      number_of_parents_(number_of_parents),
      mutation_chance_(muation_chance),
      two_opt_step_count_(two_opt_step_count),
      two_opt_initial_step_count_(two_opt_initial_step_count_),
      optimal_solution_cost_(INT16_MAX),
      best_solution_index_(0) {
  switch (initial_solution_) {
    case InitialSolution::Random: {
      const int size = instance->getSize();
      for (int i = 0; i < population_size; i++) {
        population_[i] = std::pair(random_permutation(size), INT16_MAX);
        population_[i].second =
            Solver::calculateObjectiveFunction(population_[i].first, instance);
      }
    } break;
    case InitialSolution::TwoOpt:
      initializeTwoOptSolutions();
      break;
  }

  switch (op) {
    case Operator::PMX:
      crossover_operator_ = std::make_shared<::PMX>();
      break;
    case Operator::Order1:
      crossover_operator_ = std::make_shared<::Order1>();
      break;
  }

  switch (mutation) {
    case MutationType::Insert:
      mutation_ = std::make_shared<mut::Insert>();
      break;
    case MutationType::Invert:
      mutation_ = std::make_shared<mut::Invert>();
      break;
    case MutationType::Swap:
      mutation_ = std::make_shared<mut::Swap>();
      break;
    case MutationType::TwoOptM:
      mutation_ = std::make_shared<mut::TwoOptMutation>(instance, two_opt_step_count_);
      break;
  }
}

bool notOk(std::vector<int>& v) { 
  return std::find(v.begin(), v.end(), -1) != v.end();
}

bool assert_correct_c(std::vector<int>& c, int size) {
  bool is_ok = true;

  is_ok &= (c.size() == size);
  if (is_ok) {
    for (int i = 0; i < size; i ++) {
      is_ok &= (c[i] == -1);
    }
  }
  return is_ok;
}

bool Genetic::step() {
  std::vector<int> parent_indecies;
  switch (selection_method_) {
    case SelectionMethod::RandomSelection: {
      auto permuation = random_permutation(population_size_);
      parent_indecies = std::vector<int>(
          permuation.begin(), permuation.begin() + number_of_parents_);
    } break;
    case SelectionMethod::Probabilistic:
      parent_indecies = getInvertProbabilisticParents();
      break;
  }

  std::vector<pair> children(number_of_parents_);
  for (int i = 0; i < number_of_parents_ / 2; i ++) {
    auto& p1 = population_[parent_indecies[2 * i]].first;
    auto& p2 = population_[parent_indecies[2 * i + 1]].first;
  
    std::vector<int> c1(instance->getSize(), -1);
    std::vector<int> c2(instance->getSize(), -1);

    crossover_operator_->cross(p1, p2, c1, c2);

    if (util::random() < mutation_chance_)
      mutation_->mutate(c1);
    if (util::random() < mutation_chance_)
      mutation_->mutate(c2);

    children[i * 2] = pair(c1, Solver::calculateObjectiveFunction(c1, instance));
    children[i * 2 + 1] = pair(c2, Solver::calculateObjectiveFunction(c2, instance));

    #ifdef CHECK_MUTATION
    if (notOk(c1)) std::cout << "C1 ERROR" << std::endl;
    if (notOk(c2)) std::cout << "C2 ERROR" << std::endl;

    if (notOk(children[i * 2].first)) std::cout << "C1& ERROR" << std::endl;
    if (notOk(children[i * 2 + 1].first)) std::cout << "C2& ERROR" << std::endl;
    #endif // CHECK_MUTATION
  }
  population_.insert(population_.end(), children.begin(), children.end());

  reducePopulation();
  for (auto& p : population_) {
    if(notOk(p.first)) std::cout << "not ok post" << std::endl;
  }
  return true;
}

int Genetic::calculateObjectiveFunction()
{
  return optimal_solution_cost_; //return population_[best_solution_index_].second;
}

/* TSPInstance::solution Genetic::getSolution()
{
  return population_[best_solution_index_].first;
} */

void Genetic::reducePopulation() {
  switch (reduction_mode_) {
    case ReductionMode::Best: {
      std::sort(population_.begin(), population_.end(),
                [](const pair& a, const pair& b) -> bool {
                  return a.second < b.second;
                });
      population_.erase(population_.begin() + population_size_,
                        population_.end());
      if (population_[0].second < optimal_solution_cost_) {
        optimal_solution_cost_ = population_[0].second;
        solution = population_[0].first;
      }
    } break;

    case ReductionMode::ProbabilisticRed: {
      std::random_device rd;
      std::mt19937 gen(rd());

      auto min_max = std::minmax_element(population_.begin(), population_.end(),
                                  [](const pair& a, const pair& b) -> bool {
                                    return a.second < b.second;
                                  });
      int min = population_[min_max.first - population_.begin()].second;
      int max = population_[min_max.second - population_.begin()].second;
      double diff = max - min;

      std::vector<int> ranges(population_.size() + 1, 0);
      std::iota(ranges.begin(), ranges.end(), 0);
      std::vector<double> wages(population_.size(), 0.0);
      for (int i = 0; i < population_.size(); i++) {
        wages[i] = pow((population_[i].second - min + 1) / diff, 16.0);
      }

      std::cout << util::toString(wages) << std::endl;

      for (int i = 0; i < number_of_parents_; i++) {
        std::piecewise_constant_distribution<double> dist(
            ranges.begin(), ranges.end(), wages.begin());

        int index = dist(gen);
        population_.erase(population_.begin() + i);
        wages.erase(wages.begin() + i);
        ranges.pop_back();
      }

      for (int i = 0; i < population_size_; i++) {
        if (population_[i].second < optimal_solution_cost_) {
          optimal_solution_cost_ = population_[i].second;
          solution = population_[i].first;
        }
      }
    } break;
  }
}

std::vector<int> Genetic::getInvertProbabilisticParents()
{
  // TODO make them members
  std::random_device rd;
  std::mt19937 gen(rd());  

  std::vector<int> ranges(population_size_ + 1, 0);
  std::iota(ranges.begin(), ranges.end(), 0);
  std::vector<double> wages(population_.size(), 0.0);
  for (int i = 0; i < wages.size(); i ++) {
    wages[i] = 1.0 / population_[i].second;
  }
  std::piecewise_constant_distribution<double> dist(
      ranges.begin(), ranges.end(), wages.begin());
  std::vector<int> results(number_of_parents_, 0);
  for (int i = 0; i < number_of_parents_; i ++) {
    results[i] = (int)dist(gen);
  }

  return results;
}

std::vector<int> Genetic::getProbabilisticCandidates(int x)
{
  // TODO make them members
  std::random_device rd;
  std::mt19937 gen(rd());  

  std::vector<int> wages(population_.size(), 0);
  for (int i = 0; i < wages.size(); i ++) {
    wages[i] = population_[i].second;
  }
  std::discrete_distribution<int> dist(wages.begin(), wages.end());
  std::vector<int> results(x, 0);
  for (int i = 0; i < x; i ++) {
    results[i] = dist(gen);
  }

  return results;
}

Genetic::pair Genetic::getTwoOptInitialSolution(TwoOptSolver* solver)
{
  auto initial_solcution = random_permutation(instance->getSize());
  solver->setSolution(initial_solcution);
  if (two_opt_initial_step_count_ > 0) {
  for (int i = 0; i < two_opt_initial_step_count_; i ++) {
    solver->step();
  }
  } else {
    while (solver->step()) {}
  }
  return pair(solver->getSolution(), solver->calculateObjectiveFunction());
}

void Genetic::initializeTwoOptSolutions()
{
  TwoOptSolver solver(instance);
  for (int i = 0; i < population_size_; i ++) {
    population_[i] = getTwoOptInitialSolution(&solver);
    std::cout << i + 1 << " /  " << population_size_ << std::endl;
  }
}