//
// Created by atepl on 12.04.2022.
//

#ifndef METAHEURISITICS_TWOOPTNEIGHBORHOOD_H
#define METAHEURISITICS_TWOOPTNEIGHBORHOOD_H

#include "Neighborhood.h"

class TwoOptNeighborhood : public Neighborhood {
    private:
        int currentObjective;
        int runTimeCost(int a, int b);
        void outerRotation(TSPInstance::solution& s, int a, int b);
        std::vector<int> currsolution;
        int size;
    public:
        std::vector<std::vector<int>> generateNeighborhood() override;
        int getObjectiveFunction(TSPInstance::solution& old, std::vector<int> move) override;
        TSPInstance::solution getNewSolution(const TSPInstance::solution &old,const std::vector<int>& move) override;
        TwoOptNeighborhood(std::shared_ptr<TSPInstance> instance);
};


#endif //METAHEURISITICS_TWOOPTNEIGHBORHOOD_H
