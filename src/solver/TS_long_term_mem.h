
#ifndef METAHEURISITICS_TS_LONG_TERM_MEM_H
#define METAHEURISITICS_TS_LONG_TERM_MEM_H


#include "TabuSearch.h"

// Prosta modyfikacja algorytmu tabu search. Gdy ścieżka, którą idzie nie daje lepszych rezultatów
// od najlepszej dotąd znalezionej po pewnym czasie, wraca do tego rozwiązania i próbuje wybrać inne
class TS_long_term_mem : public TabuSearch {
protected:
    void updateSolution() override;
    void updateTabuList(const std::vector<int> &addToTabu) override;

    // zapamiętana lista tabu globalnie najlepszego rozwiązania solution
    std::list<std::vector<int>> solutionTabuList;

    // ile iteracji algorytmu minęło od znalezienia najlepszego rozwiązania. jeśli przekrzacza ona
    // maxMovesWithoutimprovement, to prawdopodobnie algorytm wpadł w cykl i potrzeba resetu
    int subMovesWithoutImprovement = 0;

    // czy dana iteracja algorytmu wystąpiła bezpośrednio po znalezieniu dotychczasowego najlepszego globalnie rozwiązania.
    // jeśli tak, to zapisz następny ruch tak, by po powrocie wybrać inna ścieżkę
    bool subMoveAfterSolutionFound = false;
    int maxSubMovesWithoutImprovement = 2 * tabuListMaxSize;
public:
    inline TS_long_term_mem(std::shared_ptr<TSPInstance> instance, TSPInstance::solution &s, std::shared_ptr<Neighborhood> n,
                            enum stoppingCondition condition = ITER_CONDITION, bool aspiration_criterium = true) :
                                    TabuSearch(instance, s, n, condition, aspiration_criterium){};
    void setTabuListSize(const int &newSize) override{
        tabuListMaxSize = newSize;
        maxSubMovesWithoutImprovement = 2 * tabuListMaxSize;
        maxMovesWithoutImprovement = 2 * tabuListMaxSize;
    }
    inline void setMovesWithoutImprovement(const int& newMaxMoves){ maxSubMovesWithoutImprovement = newMaxMoves; }
};


#endif //METAHEURISITICS_TS_LONG_TERM_MEM_H
