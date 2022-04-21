
#include "Neighborhood.h"

Neighborhood::Neighborhood(std::shared_ptr<TSPInstance> instance, bool naive_mode) : instance(instance) {
    this->size = instance->getSize();
    this->naive_mode=naive_mode;
}

int Neighborhood::runTimeCost(int a, int b) {
    return instance->getCost(currSolution[(size + a) % size], currSolution[(size + b) % size]);
}
