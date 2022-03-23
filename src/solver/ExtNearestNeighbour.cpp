

#include "ExtNearestNeighbour.h"

#include <utility>

ExtNearestNeighbour::ExtNearestNeighbour(std::shared_ptr<TSPInstance> instance) : Solver(std::move(instance)) {
    setupInitialSolution();
    k = 0;
}

bool ExtNearestNeighbour::step() {
    if(k >= instance->getSize()) return false;
    NearestNeighbour nn(instance, k);
    nn.iterate();
    if(calculateObjectiveFunction(nn.getSolution()) <= calculateObjectiveFunction(solution)) solution = nn.getSolution();
    k++;
    return true;
}