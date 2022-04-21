
#ifndef METAHEURISITICS_SWAP_H
#define METAHEURISITICS_SWAP_H

#include "Neighborhood.h"

class Swap : public Neighborhood{
protected:

public:
    std::vector<std::vector<int>> generateNeighborhood();
    int getObjectiveFunction(TSPInstance::solution& old, std::vector<int> move);
    TSPInstance::solution getNewSolution(const TSPInstance::solution &old,const std::vector<int>& move);
    Swap(std::shared_ptr<TSPInstance> instance, bool naive_mode = false);

};


#endif //METAHEURISITICS_SWAP_H
