#include "K_RandomSolver.h"
#include <numeric>

bool K_RandomSolver::step(){
    if(k <= 0) return false;
    std::shuffle(currSolution.begin(), currSolution.end(), rng);
    int i = calculateObjectiveFunction(currSolution);
    if(i < calculateObjectiveFunction(solution)) K_RandomSolver::setSolution(currSolution);
    k--;
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

K_RandomSolver::K_RandomSolver(std::shared_ptr<TSPInstance> instance, int k) : Solver(instance){
    Solver::setupInitialSolution();
    setupInitialCurrSolution();
    previous = current = std::chrono::high_resolution_clock::now();
    rng.seed(std::chrono::system_clock::now().time_since_epoch().count());
    this->k = k;
}

