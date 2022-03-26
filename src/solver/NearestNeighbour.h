#ifndef METAHEURISITICS_NEARESTNEIGHBOUR_H
#define METAHEURISITICS_NEARESTNEIGHBOUR_H


#include <chrono>
#include "Solver.h"

class NearestNeighbour : public Solver{
    protected:
        std::vector<int> unvisited;
        int startingPoint;

    public:
        NearestNeighbour(const std::shared_ptr<TSPInstance>& instance, int startingPoint);
        bool step() override;
        int getNearestNeighbour();
};


#endif //METAHEURISITICS_NEARESTNEIGHBOUR_H
