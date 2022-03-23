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

int Solver::calculateObjectiveFunction(TSPInstance::solution s)
{
    int sum = 0;
    for (int i = 1; i < s.size(); i++)
        sum += instance->getCost(s[i - 1], s[i]);
    sum += instance->getCost(s[s.size() - 1], s[0]);
    return sum;
}

int Solver::calculateObjectiveFunction()
{
    return Solver::calculateObjectiveFunction(solution);
}
