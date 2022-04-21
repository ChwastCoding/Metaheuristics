
#include <algorithm>
#include "Invert.h"
#include "../solver/Solver.h"



std::vector<std::vector<int>> Invert::generateNeighborhood() {

    if(instance->getIsSymetric()){
        std::vector<std::vector<int>> neighborhood;
        for (int i = 0; i < size; i++) {
            for (int j = i + 1; j < size && !(i == 0 && j == size - 1); j ++){
                std::vector<int> a(2);
                a[0] = i, a[1] = j;
                neighborhood.push_back(a);
            }
        }
        return neighborhood;
    }
    else{
        std::vector<std::vector<int>> neighborhood;
        for (int i = 0; i < size; i ++) {
            for (int j = 0; j < size; j ++) {
                if (i == j) continue;
                std::vector<int> move(2);
                move[0] = i, move[1] = j;
                neighborhood.push_back(move);
            }
        }
        return neighborhood;
    }
}

int Invert::getObjectiveFunction(TSPInstance::solution& newSolution, std::vector<int> move) {
    if (newSolution != currSolution){
        currSolution = TSPInstance::solution (newSolution);
        size = currSolution.size();
        currentObjective = Solver::calculateObjectiveFunction(currSolution, instance);
    }

    if(instance->getIsSymetric() && !naive_mode){
        int res = currentObjective - runTimeCost(move[0] - 1, move[0]) - runTimeCost(move[1], move[1] + 1)
                  + runTimeCost(move[0] - 1, move[1]) + runTimeCost(move[0], move[1] + 1);
        return res;
    }
    else{
        auto copy = TSPInstance::solution(currSolution);
        if (move[0] < move[1]) std::reverse(copy.begin() + move[0], copy.begin() + move[1] + 1);
        else outerRotation(copy, move[0], move[1]);

        int res = Solver::calculateObjectiveFunction(copy, instance);
        return res;
    }
}

TSPInstance::solution Invert::getNewSolution(const TSPInstance::solution &solution, const std::vector<int>& move) {
    TSPInstance::solution s(solution);
    if(instance->getIsSymetric()){
        std::reverse(s.begin() + move[0], s.begin() + move[1] + 1);
    }
    else{
        if (move[0] < move[1]) std::reverse(s.begin() + move[0], s.begin() + move[1] + 1);
        else outerRotation(s, move[0], move[1]);
    }

    return s;
}



void Invert::outerRotation(TSPInstance::solution& s, int a, int b)
{
    int c;
    do {
        std::swap(s[a], s[b]);
        c = a;
        if (++a == s.size()) a = 0;
        if (--b == -1) b = s.size() - 1;
    } while (c != b && b != a);
}