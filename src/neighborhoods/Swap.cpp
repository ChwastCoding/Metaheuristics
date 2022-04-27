
#include "Swap.h"

int Swap::getObjectiveFunction(std::vector<int> move) {
    move[0] = cityIndex[move[0]], move[1] = cityIndex[move[1]];
    if(!naive_mode){
        if((move[1] + 1) % size == move[0]){
            std::swap(move[0], move[1]);
            int res = currentObjective - runTimeCost(move[0] - 1, move[0]) - runTimeCost(move[0], move[1])
                        - runTimeCost(move[1], move[1] + 1)
                        + runTimeCost(move[0] - 1, move[1]) + runTimeCost(move[0], move[1] + 1)
                        + runTimeCost(move[1], move [0]);
            return res;
        }
        if((move[0] + 1) % size == move [1]){
            int res = currentObjective - runTimeCost(move[0] - 1, move[0]) - runTimeCost(move[0], move[1])
                      - runTimeCost(move[1], move[1] + 1)
                      + runTimeCost(move[0] - 1, move[1]) + runTimeCost(move[0], move[1] + 1)
                      + runTimeCost(move[1], move [0]);
            return res;
        }
        int res = currentObjective
                   - runTimeCost(move[0] - 1, move[0]) - runTimeCost(move[0], move[0] + 1)
                   - runTimeCost(move[1] - 1, move[1]) - runTimeCost(move[1], move[1] + 1)
                   + runTimeCost(move[0] - 1, move[1]) + runTimeCost(move[1], move[0] + 1)
                   + runTimeCost(move[1] - 1, move[0]) + runTimeCost(move[0], move[1] + 1);
        return res;
    }
    else{
        TSPInstance::solution solution = getNewSolution(move);
        int res = Solver::calculateObjectiveFunction(solution, instance);
        return res;
    }
}

TSPInstance::solution Swap::getNewSolution(std::vector<int> move) {
    move[0] = cityIndex[move[0]], move[1] = cityIndex[move[1]];
    TSPInstance::solution copy(currSolution);
    std::iter_swap(copy.begin() + move[0], copy.begin() + move[1]);
    return copy;
}

Swap::Swap(std::shared_ptr<TSPInstance> instance, bool naive_mode) : Neighborhood(instance, naive_mode) {
    generateNeighborhood();
}

void Swap::generateNeighborhood() {

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

std::vector<std::vector<int>> Swap::getReverseMove(const std::vector<int> &move) {
    std::vector<std::vector<int>> reverseList;
    std::vector<int> reverseMove;
    reverseMove.push_back(move[1]);
    reverseMove.push_back(move[0]);
    reverseList.push_back(reverseMove);
    reverseList.push_back(move);
    return reverseList;
}

