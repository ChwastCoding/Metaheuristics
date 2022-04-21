//
// Created by atepl on 12.04.2022.
//

#ifndef METAHEURISITICS_TABUSEARCH_H
#define METAHEURISITICS_TABUSEARCH_H


#include <map>
#include "../tsp_data/TSPInstance.h"
#include "Solver.h"
#include "../neighborhoods/Neighborhood.h"

class TabuSearch : public Solver{
    private:


    std::shared_ptr<Neighborhood> n;
        std::list<std::vector<int>> tabuList;
        TSPInstance::solution currSolution;
        int tabuListMaxSize = 20;


        //tymczasowe elementy do warunku końca, mają być przeniesione do osobnej klasy
        int k = 0, kmax=100;

    public:
        TabuSearch(std::shared_ptr<TSPInstance> instance, TSPInstance::solution &s, std::shared_ptr<Neighborhood> n);

        bool stoppingCondition();

        bool step() override;
};


#endif //METAHEURISITICS_TABUSEARCH_H
