
#ifndef METAHEURISITICS_INVERT_H
#define METAHEURISITICS_INVERT_H

#include "Neighborhood.h"
#include "stdexcept"
class Invert : public Neighborhood {
    private:
        void outerRotation(TSPInstance::solution& s, int a, int b);
    protected:
        void generateNeighborhood() override;
    public:
        int getObjectiveFunction(std::vector<int> move) override;
        TSPInstance::solution getNewSolution(std::vector<int> move) override;
        std::vector<std::vector<int>> getReverseMove(const std::vector<int>& move) override;
        inline Invert(std::shared_ptr<TSPInstance> instance, bool naive_mode = false) : Neighborhood(instance, naive_mode) {
            if(!naive_mode && !instance->getIsSymetric()) throw std::runtime_error("Asymmetric instance is only solvable in naive mode");
            generateNeighborhood();
        }
};


#endif //METAHEURISITICS_INVERT_H
