
#include "Insert.h"


int Insert::getObjectiveFunction(std::vector<int> move) {
    move[0] = cityIndex[move[0]], move[1] = cityIndex[move[1]];
    if(!naive_mode){
        if(move[1]-move[0] == 0 || move[1]-move[0] == 1 || ( move[0]==size-1 && move[1] == 0)) return currentObjective;
        int res = currentObjective - runTimeCost(move[0]-1, move[0]) - runTimeCost(move[0], move[0] + 1)
                - runTimeCost(move[1] - 1, move[1]) + runTimeCost(move[0] - 1, move[0] + 1)
                + runTimeCost(move[1] - 1, move[0]) + runTimeCost(move[0], move [1]);
        return res;
    }
    else{
        TSPInstance::solution solution = getNewSolution(move);
        int res = Solver::calculateObjectiveFunction(solution, instance);
        return res;
    }
}

TSPInstance::solution Insert::getNewSolution(std::vector<int> move) {
    //zmiana numerów miast na ich pozycje na reprezentacji rozwiązania
    move[0] = cityIndex[move[0]], move[1] = cityIndex[move[1]];
    std::vector<int> newSolution(currSolution);
    int temp = newSolution[move[0]];
    int i;
    if(move[0] > move[1]){
        for(i = move[0]; i > move[1]; i--){
            newSolution[i] = newSolution[i-1];
        }
    }
    else{
        for(i = move[0]; i < move[1] - 1; i++){
            newSolution[i] = newSolution[i+1];
        }
    }
    newSolution[i] = temp;
    return newSolution;
}

void Insert::generateNeighborhood() {
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(i==j) continue;
            std::vector<int> move(2);
            move[0] = i, move[1] = j;
            neighborhood.push_back(move);
        }
    }
}

std::vector<std::vector<int>> Insert::getReverseMove(const std::vector<int> &move) {
    std::vector<std::vector<int>> reverseList;
    std::vector<int> reverseMove;
    reverseMove.push_back(move[0]);
    reverseMove.push_back(currSolution[(cityIndex[move[0]] + 1) % size]);
    reverseList.push_back(reverseMove);
    reverseList.push_back(move);
    return reverseList;
}
