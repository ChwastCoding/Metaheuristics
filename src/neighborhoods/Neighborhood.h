
#ifndef METAHEURISITICS_NEIGHBORHOOD_H
#define METAHEURISITICS_NEIGHBORHOOD_H


#include <list>
#include <algorithm>
#include <memory>
#include "../tsp_data/TSPInstance.h"

class Neighborhood {
protected:
    std::shared_ptr<TSPInstance> instance;
    int size;
    int currentObjective;
    int runTimeCost(int a, int b);
    std::vector<int> currSolution;
    bool naive_mode;

public:
    virtual std::vector<std::vector<int>> generateNeighborhood() = 0;
    virtual int getObjectiveFunction(TSPInstance::solution& old, std::vector<int> move) = 0;
    virtual TSPInstance::solution getNewSolution(const TSPInstance::solution &old,const std::vector<int>& move) = 0;
    Neighborhood(std::shared_ptr<TSPInstance> instance, bool naive_mode = false);
};


#endif //METAHEURISITICS_NEIGHBORHOOD_H
