
#ifndef METAHEURISITICS_SWAP_H
#define METAHEURISITICS_SWAP_H

#include "Neighborhood.h"

class Swap : public Neighborhood{
protected:
    void generateNeighborhood() override;
public:
    int getObjectiveFunction(std::vector<int> move) override;
    TSPInstance::solution getNewSolution(std::vector<int> move) override;
    std::vector<std::vector<int>> getReverseMove(const std::vector<int>& move) override;
    Swap(std::shared_ptr<TSPInstance> instance, bool naive_mode = false);
};


#endif //METAHEURISITICS_SWAP_H
