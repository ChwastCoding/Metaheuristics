#include "DummySolver.h"

#include <numeric>

#include "../util.h"

DummySolver::DummySolver(std::shared_ptr<TSPInstance> instance) : Solver(instance) {
    setupInitialSolution();
    previous = current = std::chrono::high_resolution_clock::now();
}

bool DummySolver::step()
{
    if (std::chrono::duration_cast<std::chrono::milliseconds>(current - previous).count() > 100) {
        previous = current;
        std::swap(solution[util::random(solution.size())], solution[util::random(solution.size())]);
    }
    current = std::chrono::high_resolution_clock::now();
    return false;
}

void DummySolver::setSolution(const TSPInstance::solution& solution)
{
    this->solution = solution;
}
