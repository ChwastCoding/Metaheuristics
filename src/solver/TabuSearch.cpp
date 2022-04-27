
#include <list>
#include "TabuSearch.h"

bool TabuSearch::step() {
    if(stoppingCondition()) return false;
    std::vector<std::vector<int>> neighborhood = n->getNeighborhood();

    // ustaw rozwiązanie, które generator otoczenia będzie przyjmował jako bazowe, więc ruch będzie aplikowany
    // nie do nowego znalezionego kandydata na rozwiązanie, a do tego, który był na początku wywołania funkcji step()
    n->setCurrSolution(bestCandidat);
    bestCandidatObjective = __INT_MAX__;
    std::vector<int> addToTabu;
    int candidateObjectiveFunction;

    std::vector<std::vector<int>>::iterator it;
    //iteruj po otoczeniu i sprawdź, czy nie jest ono zabronione
    for(it = neighborhood.begin(); it != neighborhood.end(); it++) {
        bool tabuElement = false;
        std::list<std::vector<int>>::iterator tabuIt;
        for (tabuIt = tabuList.begin(); tabuIt != tabuList.end(); tabuIt++) {
            if (*tabuIt == *it) {
                //kryterium aspiracji
                if(aspiration_criterium && n->getObjectiveFunction(*it) < solutionObjective){
                    tabuElement = false;
                    for(const std::vector<int>& move : n->getReverseMove(*it))
                        tabuList.remove(move);
                }
                else tabuElement = true;
                break;
            }
        }
        candidateObjectiveFunction = n->getObjectiveFunction(*it);
        //jeśli kandydat jest lepszy od dotychczasowego, ustal nowego kandydata
        if(!tabuElement && candidateObjectiveFunction < bestCandidatObjective){
            bestCandidat = n->getNewSolution(*it);
            bestCandidatObjective = candidateObjectiveFunction;
            addToTabu = std::vector<int>(*it);
        }
    }

    updateTabuList(addToTabu);

    updateSolution();
    return true;
}

TabuSearch::TabuSearch(std::shared_ptr<TSPInstance> instance, TSPInstance::solution& s, std::shared_ptr<Neighborhood> n,
                       enum stoppingCondition condition, bool aspiration_criterium) : Solver(instance) , n(n){
    this->aspiration_criterium = aspiration_criterium;
    this->condition = condition;
    this->solution = TSPInstance::solution(s);
    solutionObjective = calculateObjectiveFunction();

    bestCandidat = TSPInstance::solution(solution);
    bestCandidatObjective = solutionObjective;
}

void TabuSearch::updateSolution() {
    //jeśli jest lepsze od dotychczasowego, zamień go
    if(bestCandidatObjective < solutionObjective){
        solution = TSPInstance::solution(bestCandidat);
        solutionObjective = bestCandidatObjective;
        movesWithoutImprovement = 0;
    }
    else{
        movesWithoutImprovement++;
    }
}

void TabuSearch::updateTabuList(const std::vector<int> &addToTabu) {
    // dodaj ruch i jego odwrotność do listy tabu
    std::vector<std::vector<int>> reverseList;
    reverseList = n->getReverseMove(addToTabu);
    for(const std::vector<int>& move : reverseList){
        tabuList.push_back(move);
        // jeśli lista tabu jest już przepełniona, wysuń z niej najstarszy element
        if(tabuList.size() > tabuListMaxSize){
            tabuList.pop_front();
        }
    }
}

bool TabuSearch::stoppingCondition() {
    switch(condition){
        case TIME_CONDITION: return timeStoppingCondition();
        case ITER_CONDITION: return iterStoppingCondition();
        case IMPROVEMENT_CONDITION: return improvementStoppingCondition();
        case NO_CONDITION: return false;
    }
    return false;
}

bool TabuSearch::timeStoppingCondition(){
    if(!has_started){
        start = std::chrono::high_resolution_clock::now();
        has_started = true;
    }
    std::chrono::time_point<std::chrono::high_resolution_clock> now = std::chrono::high_resolution_clock::now();
    if((now - start).count() > max_time) return true;
    return false;
}

bool TabuSearch::iterStoppingCondition() {
    if(iteration >= max_iteration) return true;
    iteration++;
    return false;
}

bool TabuSearch::improvementStoppingCondition() {
    if(movesWithoutImprovement >= maxMovesWithoutImprovement) return true;
    return false;
}


