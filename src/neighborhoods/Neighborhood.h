//
// Created by atepl on 12.04.2022.
//

#ifndef METAHEURISITICS_NEIGHBORHOOD_H
#define METAHEURISITICS_NEIGHBORHOOD_H


#include <list>
#include <memory>
#include "../tsp_data/TSPInstance.h"

class Neighborhood {
protected:
    std::shared_ptr<TSPInstance> instance;

public:
    virtual std::vector<std::vector<int>> generateNeighborhood() = 0;
    virtual int getObjectiveFunction(TSPInstance::solution& old, std::vector<int> move) = 0;
    virtual TSPInstance::solution getNewSolution(const TSPInstance::solution &old,const std::vector<int>& move) = 0;
    Neighborhood(std::shared_ptr<TSPInstance> instance);
};


#endif //METAHEURISITICS_NEIGHBORHOOD_H
