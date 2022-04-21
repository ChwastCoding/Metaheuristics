
#ifndef METAHEURISITICS_INVERT_H
#define METAHEURISITICS_INVERT_H

#include "Neighborhood.h"

class Invert : public Neighborhood {
    private:


    void outerRotation(TSPInstance::solution& s, int a, int b);
    public:
        std::vector<std::vector<int>> generateNeighborhood() override;
        int getObjectiveFunction(TSPInstance::solution& old, std::vector<int> move) override;
        TSPInstance::solution getNewSolution(const TSPInstance::solution &old,const std::vector<int>& move) override;
        inline Invert(std::shared_ptr<TSPInstance> instance, bool naive_mode = false) : Neighborhood(instance, naive_mode) {
            if(!naive_mode && !instance->getIsSymetric()) throw std::runtime_error("Asymmetric instance is only solvable in naive mode");
        }
};


#endif //METAHEURISITICS_INVERT_H
