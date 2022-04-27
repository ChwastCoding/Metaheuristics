
#ifndef METAHEURISITICS_NEIGHBORHOOD_H
#define METAHEURISITICS_NEIGHBORHOOD_H


#include <list>
#include <algorithm>
#include <memory>
#include "../tsp_data/TSPInstance.h"
#include "../solver/Solver.h"

class Neighborhood {
protected:
    const std::shared_ptr<TSPInstance> instance;
    const int size;
    const bool naive_mode;

    int currentObjective;
    std::vector<int> currSolution;
    std::vector<std::vector<int>> neighborhood;
    std::vector<int> cityIndex;

    int runTimeCost(int a, int b);
    void generateCityIndex();
    Neighborhood(std::shared_ptr<TSPInstance> instance, bool naive_mode = false);

    virtual void generateNeighborhood() = 0;

public:

    virtual int getObjectiveFunction(std::vector<int> move) = 0;
    virtual TSPInstance::solution getNewSolution(std::vector<int> move) = 0;
    virtual std::vector<std::vector<int>> getReverseMove(const std::vector<int>& move) = 0;

    inline const std::vector<std::vector<int>>& getNeighborhood(){ return neighborhood; }
    inline const std::vector<int>& getCurrSolution(){ return currSolution; }
    inline int getCurrObjective(){ return currentObjective; }
    void setCurrSolution(const TSPInstance::solution& newSolution);
};


#endif //METAHEURISITICS_NEIGHBORHOOD_H
