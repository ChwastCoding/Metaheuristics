

#include "ExtNearestNeighbour.h"

#include <utility>

ExtNearestNeighbour::ExtNearestNeighbour(std::shared_ptr<TSPInstance> instance) : Solver(std::move(instance)) {
    setupInitialSolution();
    k = 0;
}

void ExtNearestNeighbour::setSolution(const TSPInstance::solution &solution) {
    this->solution = solution;
}

bool ExtNearestNeighbour::step() {
    if(k >= instance->getSize()) return false;
    NearestNeighbour nn(instance, k);
    nn.iterate();
    if(calculateObjectiveFunction(nn.getSolution()) <= calculateObjectiveFunction(solution)) setSolution(nn.getSolution());
    k++;
    return true;
}