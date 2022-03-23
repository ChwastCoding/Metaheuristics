#include "K_RandomSolver.h"
#include <numeric>
#include <utility>

K_RandomSolver::K_RandomSolver(std::shared_ptr<TSPInstance> instance, int k) : Solver(std::move(instance)){
    Solver::setupInitialSolution();
    setupInitialCurrSolution();
    previous = current = std::chrono::high_resolution_clock::now();
    rng.seed(std::chrono::system_clock::now().time_since_epoch().count());
    this->k = k;
}

bool K_RandomSolver::step(){
    if(k <= 0) return false;
    if (std::chrono::duration_cast<std::chrono::milliseconds>(current - previous).count() > 100) {
        previous = current;
        std::shuffle(currSolution.begin(), currSolution.end(), rng);
        if(Solver::calculateObjectiveFunction(currSolution) < Solver::calculateObjectiveFunction(solution)) K_RandomSolver::setSolution(currSolution);
        k--;
    }
    current = std::chrono::high_resolution_clock::now();
    return true;
}

void K_RandomSolver::setupInitialCurrSolution()
{
    currSolution.resize(instance->getSize());
    std::iota(currSolution.begin(), currSolution.end(), 0);
}

void K_RandomSolver::setSolution(const TSPInstance::solution &solution) {
    this->solution = solution;
}

