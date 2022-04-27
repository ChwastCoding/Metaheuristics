
#ifndef METAHEURISITICS_INSERT_H
#define METAHEURISITICS_INSERT_H

#include "Neighborhood.h"

class Insert : public Neighborhood{
protected:
    void generateNeighborhood() override;
public:
    int getObjectiveFunction(std::vector<int> move) override;
    TSPInstance::solution getNewSolution(std::vector<int> move) override;
    std::vector<std::vector<int>> getReverseMove(const std::vector<int>& move) override;
    inline Insert(std::shared_ptr<TSPInstance> instance, bool naive_mode = false) : Neighborhood(instance, naive_mode){
        generateNeighborhood();
    };
};


#endif //METAHEURISITICS_INSERT_H
