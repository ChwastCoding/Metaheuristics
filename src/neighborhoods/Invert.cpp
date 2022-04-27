
#include <algorithm>
#include "Invert.h"


int Invert::getObjectiveFunction(std::vector<int> move) {
    move[0] = cityIndex[move[0]], move[1] = cityIndex[move[1]];
    if(!naive_mode){
        if(move[0] > move[1]) std::swap(move[0], move[1]);
        if(move[0] == 0 && move[1] == size - 1) return currentObjective;
        int res = currentObjective - runTimeCost(move[0] - 1, move[0]) - runTimeCost(move[1], move[1] + 1)
                  + runTimeCost(move[0] - 1, move[1]) + runTimeCost(move[0], move[1] + 1);
        return res;
    }
    else{
        if( instance->getIsSymetric()){
            auto copy = TSPInstance::solution(currSolution);
            if(move[0] > move[1]) std::swap(move[0], move[1]);
            std::reverse(copy.begin() + move[0], copy.begin() + move[1] + 1);
            int res = Solver::calculateObjectiveFunction(copy, instance);
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
}

TSPInstance::solution Invert::getNewSolution(std::vector<int> move) {
    move[0] = cityIndex[move[0]], move[1] = cityIndex[move[1]];
    auto s = TSPInstance::solution (currSolution);
    if(instance->getIsSymetric()){
        if(move[0] > move[1]) std::swap(move[0], move[1]);
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

void Invert::generateNeighborhood() {
    if(instance->getIsSymetric()){
        for (int i = 0; i < size; i++) {
            for (int j = i + 1; j < size; j ++){
                std::vector<int> a(2);
                a[0] = i, a[1] = j;
                neighborhood.push_back(a);
            }
        }
    }
    else{
        for (int i = 0; i < size; i ++) {
            for (int j = 0; j < size; j ++) {
                if (i == j) continue;
                std::vector<int> move(2);
                move[0] = i, move[1] = j;
                neighborhood.push_back(move);
            }
        }
    }
}

std::vector<std::vector<int>> Invert::getReverseMove(const std::vector<int> &move) {
    std::vector<std::vector<int>> reverseList;
    std::vector<int> reverseMove;
    reverseMove.push_back(move[1]);
    reverseMove.push_back(move[0]);
    reverseList.push_back(reverseMove);
    if(instance->getIsSymetric()){
        reverseList.push_back(move);
    }
    return reverseList;
}
