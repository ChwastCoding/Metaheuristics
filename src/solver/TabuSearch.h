//
// Created by atepl on 12.04.2022.
//

#ifndef METAHEURISITICS_TABUSEARCH_H
#define METAHEURISITICS_TABUSEARCH_H


#include <map>
#include "../tsp_data/TSPInstance.h"
#include "Solver.h"
#include "../neighborhoods/Neighborhood.h"

#include <chrono>

class TabuSearch : public Solver{
    protected:
        // generator otoczenia
        std::shared_ptr<Neighborhood> n;
        std::list<std::vector<int>> tabuList;

        // najlepsze rozwiązanie z wybranego otoczenia - niekoniecznie lepsze od solution!
        TSPInstance::solution bestCandidat;

        // funkcja celu najlepszego rozwiązania z wybranego otoczenia
        int bestCandidatObjective;
        int solutionObjective;

        //rozmiar listy tabu
        int tabuListMaxSize = 56;

        //czy w algorytmie jest stosowane kryterium aspiracji: jeśli rozwiązanie jest lepsze od globalnego rozwiązania
        //solution, a jest na liście tabu to złam tabu i pozwól go wybrać
        bool aspiration_criterium;



        // po znalezionym kandydacie na rozwiązanie sprawdź, czy jest ono lepsze od dotychczas znalezionego rozwiązania
        virtual void updateSolution();

        // dodaj do listy tabu reprezentacje ruchu
        virtual void updateTabuList(const std::vector<int> &addToTabu);

        bool timeStoppingCondition();
        bool iterStoppingCondition();
        bool improvementStoppingCondition();
        std::chrono::time_point<std::chrono::high_resolution_clock> start;
        double max_time = 1000;
        bool has_started = false;

        int iteration = 0, max_iteration=200;

        //ile ruchów minęło od znalezienia najleszpego rozwiązania - służy do kryterium stopu
        int movesWithoutImprovement = 0;

        int maxMovesWithoutImprovement = 2* tabuListMaxSize;


    public:
        enum stoppingCondition{
            TIME_CONDITION,
            ITER_CONDITION,
            IMPROVEMENT_CONDITION,
            NO_CONDITION
        };

        TabuSearch(std::shared_ptr<TSPInstance> instance, TSPInstance::solution &s, std::shared_ptr<Neighborhood> n,
                   enum stoppingCondition condition = ITER_CONDITION, bool aspiration_criterium = true);

        virtual bool stoppingCondition();

        bool step() override;

        void setMaxIter(const int& newMax){ max_iteration = newMax; }
        void setMaxTime(const double& newMax){ max_time = newMax; }
        virtual void setTabuListSize(const int& newSize){ tabuListMaxSize = newSize; maxMovesWithoutImprovement = 2* tabuListMaxSize;}

    protected:
        enum stoppingCondition condition;
};


#endif //METAHEURISITICS_TABUSEARCH_H
