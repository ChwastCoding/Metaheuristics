
#ifndef METAHEURISITICS_INSERT_H
#define METAHEURISITICS_INSERT_H

#include "Neighborhood.h"

class Insert : public Neighborhood{

public:
    std::vector<std::vector<int>> generateNeighborhood() override;
    int getObjectiveFunction(TSPInstance::solution& old, std::vector<int> move) override;
    TSPInstance::solution getNewSolution(const TSPInstance::solution &old,const std::vector<int>& move) override;
    inline Insert(std::shared_ptr<TSPInstance> instance, bool naive_mode = false) : Neighborhood(instance, naive_mode){};
};


#endif //METAHEURISITICS_INSERT_H
