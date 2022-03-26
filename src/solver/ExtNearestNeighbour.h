
#ifndef METAHEURISITICS_EXTNEARESTNEIGHBOUR_H
#define METAHEURISITICS_EXTNEARESTNEIGHBOUR_H


#include "Solver.h"
#include "NearestNeighbour.h"

class ExtNearestNeighbour : public Solver{
    protected:
        int k;
    public:
        ExtNearestNeighbour(const std::shared_ptr<TSPInstance> &instance);
        bool step() override;
        void setSolution(const TSPInstance::solution& solution);

};


#endif //METAHEURISITICS_EXTNEARESTNEIGHBOUR_H
