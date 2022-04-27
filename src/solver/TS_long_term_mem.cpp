
#include "TS_long_term_mem.h"

void TS_long_term_mem::updateSolution() {
    // jeśli znalezione rozwiązanie jest lepsze
    if(bestCandidatObjective < solutionObjective){
        // ustaw je jako nowe najlepsze
        solution = TSPInstance::solution(bestCandidat);
        solutionObjective = bestCandidatObjective;
        subMovesWithoutImprovement = 0;
        movesWithoutImprovement = 0;
        //zapisz listę tabu w tym kroku, by w razie niepowodzenia przywrócić ją
        solutionTabuList = std::list<std::vector<int>>(tabuList);
        subMoveAfterSolutionFound = true;
    }
    else{
        //zwiększ licznik kroków od ostatniej poprawy
        subMovesWithoutImprovement ++;
        //jeśli przekroczono maksymalną ilość ruchów
        if(subMovesWithoutImprovement > maxSubMovesWithoutImprovement){
            //przywróć nalepsze rozwiązanie
            bestCandidat = TSPInstance::solution(solution);
            bestCandidatObjective = solutionObjective;
            subMovesWithoutImprovement = 0;
            //zwiększ ilość ruchów bez poprawy, czyli prób znalezienia lepszego rozwiązania od dotychczasowego,
            //startując z niego
            movesWithoutImprovement++;
            //przywróc listę tabu
            tabuList = solutionTabuList;
            subMoveAfterSolutionFound = true;
        }
    }
}

void TS_long_term_mem::updateTabuList(const std::vector<int> &addToTabu) {
    std::vector<std::vector<int>> reverseList;
    reverseList = n->getReverseMove(addToTabu);
    for(const std::vector<int>& move : reverseList){
        tabuList.push_back(move);
        if(tabuList.size() > tabuListMaxSize){
            tabuList.pop_front();
        }
        //jeśli jest to ruch po znalezieniu najlepszego globalnie rozwiązania, zapisz w
        //zapamiętanej liście solutionTabuList, gdzie algorytm poszedł, żeby po przywróceniu tego rozwiązania
        //wybrać inną ścieżkę
        if(subMoveAfterSolutionFound){
            solutionTabuList.push_back(move);
            if(solutionTabuList.size() > tabuListMaxSize){
                solutionTabuList.pop_front();
            }
        }
    }
    subMoveAfterSolutionFound = false;
}
