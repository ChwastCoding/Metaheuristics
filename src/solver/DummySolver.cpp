#include "DummySolver.h"
#include <numeric>

TSPInstance::solution DummySolver::solve(std::shared_ptr<TSPInstance> instance)
{
    if (cachedSolution.empty()){
        std::vector<int> solution(instance->getSize());
        std::iota(solution.begin(), solution.end(), 0);
        return solution;
    } else {
        return cachedSolution;
    }
}
