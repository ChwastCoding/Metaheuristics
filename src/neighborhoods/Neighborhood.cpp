
#include "Neighborhood.h"

Neighborhood::Neighborhood(std::shared_ptr<TSPInstance> instance, bool naive_mode) : instance(instance), size(instance->getSize()),
    cityIndex(size), naive_mode(naive_mode) {
}

int Neighborhood::runTimeCost(int a, int b) {
    return instance->getCost(currSolution[(size + a) % size], currSolution[(size + b) % size]);
}

void Neighborhood::setCurrSolution(const TSPInstance::solution &newSolution) {
    currSolution = std::vector<int>(newSolution);
    currentObjective = Solver::calculateObjectiveFunction(currSolution, instance);
    generateCityIndex();
}

void Neighborhood::generateCityIndex() {
    for(int i = 0; i < size; i++){
        cityIndex[currSolution[i]] = i;
    }
}
