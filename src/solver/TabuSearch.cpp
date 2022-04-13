//
// Created by atepl on 12.04.2022.
//

#include <list>
#include "TabuSearch.h"

bool TabuSearch::step() {
    if(stoppingCondition()) return false;
    std::vector<std::vector<int>> neighborhood = n->generateNeighborhood();
    std::vector<std::vector<int>>::iterator it;
    currSolution = TSPInstance::solution (solution);

    int currObjectiveFunction = calculateObjectiveFunction(currSolution);
    std::vector<int> addToTabu;

    for(it = neighborhood.begin(); it != neighborhood.end(); it++) {
        bool tabuElement = false;
        std::list<std::vector<int>>::iterator tabuIt;
        for (tabuIt = tabuList.begin(); tabuIt != tabuList.end(); tabuIt++) {
            if (*tabuIt == *it) {
                tabuElement = true;
                break;
            }
        }
        int newObjectiveFunction = n->getObjectiveFunction(solution, *it);
        if(!tabuElement && newObjectiveFunction < currObjectiveFunction){
            currSolution = n->getNewSolution(solution, *it);
            currObjectiveFunction = newObjectiveFunction;
            addToTabu = std::vector<int>(*it);
        }
    }
    if(!addToTabu.empty()) tabuList.push_back(addToTabu);
    if(tabuList.size() > tabuListMaxSize){
        tabuList.pop_front();
    }

    solution = currSolution;
    return true;
}

TabuSearch::TabuSearch(std::shared_ptr<TSPInstance> instance, TSPInstance::solution& s, std::shared_ptr<Neighborhood> n) : Solver(instance) , n(n){
    this->solution = TSPInstance::solution(s);
}


//prosty warunek końca, do rozwinięcia
bool TabuSearch::stoppingCondition() {
    if(k >= kmax) return true;
    k++;
    return false;
}
