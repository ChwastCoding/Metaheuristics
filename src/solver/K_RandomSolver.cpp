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

void K_RandomSolver::setSolution(const TSPInstance::solution &solution) {
    this->solution = solution;
}

K_RandomSolver::K_RandomSolver(const std::shared_ptr<TSPInstance>& instance, int k) : Solver(instance), currSolution(instance->getSize()){
    setupInitialSolution();
    std::iota(currSolution.begin(), currSolution.end(), 0);
    rng.seed(std::chrono::system_clock::now().time_since_epoch().count());
    this->k = k;
}

