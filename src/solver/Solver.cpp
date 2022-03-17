#include "Solver.h"
#include <numeric>

void Solver::setupInitialSolution()
{
    solution.resize(instance->getSize());
    std::iota(solution.begin(), solution.end(), 0);    
}

Solver::Solver(std::shared_ptr<TSPInstance> instance) : instance(instance) {}

TSPInstance::solution Solver::getSolution()
{
    return solution;
}

int Solver::calculateObjectiveFunction()
{
    int sum = 0;
    for (int i = 1; i < solution.size(); i++)
        sum += instance->getCost(i - 1, i);
    return sum += instance->getCost(solution.size() - 1, 0);
}
