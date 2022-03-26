

#include "ExtNearestNeighbour.h"


ExtNearestNeighbour::ExtNearestNeighbour(const std::shared_ptr<TSPInstance>& instance) : Solver(instance) {
    setupInitialSolution();
    k = 0;
}

void ExtNearestNeighbour::setSolution(const TSPInstance::solution &solution) {
    this->solution = solution;
}

bool ExtNearestNeighbour::step() {
    if(k >= instance->getSize()) return false;
    NearestNeighbour nn(instance, k);
    while(nn.step());
    if(calculateObjectiveFunction(nn.getSolution()) <= calculateObjectiveFunction(solution)) setSolution(nn.getSolution());
    k++;
    return true;
}