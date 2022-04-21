#ifndef METAHEURISITICS_NEARESTNEIGHBOUR_H
#define METAHEURISITICS_NEARESTNEIGHBOUR_H


#include <chrono>
#include "Solver.h"

class NearestNeighbour : public Solver{
    protected:
        std::chrono::time_point<std::chrono::high_resolution_clock> previous, current;
        std::vector<int> unvisited;
        int startingPoint;

    public:
        NearestNeighbour(std::shared_ptr<TSPInstance> instance, int startingPoint);
        bool step() override;
        void setupUnvisitedNodes();
        void iterate();

    int getNearestNeighbour();
};


#endif //METAHEURISITICS_NEARESTNEIGHBOUR_H
