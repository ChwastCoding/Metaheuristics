
#include "Insert.h"
#include "../solver/Solver.h"

std::vector<std::vector<int>> Insert::generateNeighborhood() {
    std::vector<std::vector<int>> neighborhood;
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(j-i == 0 || j-i == 1 || ( i==size-1 && j == 0)) continue;
            std::vector<int> move(2);
            move[0] = i, move[1] = j;
            neighborhood.push_back(move);
        }
    }
    return neighborhood;
}

int Insert::getObjectiveFunction(TSPInstance::solution &newSolution, std::vector<int> move) {
    if (newSolution != currSolution){
        currSolution = TSPInstance::solution (newSolution);
        size = int(currSolution.size());
        currentObjective = Solver::calculateObjectiveFunction(currSolution, instance);
    }
    if(!naive_mode){
        if(move[1]-move[0] == 0 || move[1]-move[0] == 1 || ( move[0]==size-1 && move[1] == 0)) return currentObjective;
        int res = currentObjective - runTimeCost(move[0]-1, move[0]) - runTimeCost(move[0], move[0] + 1)
                - runTimeCost(move[1] - 1, move[1]) + runTimeCost(move[0] - 1, move[0] + 1)
                + runTimeCost(move[1] - 1, move[0]) + runTimeCost(move[0], move [1]);
        return res;
    }
    else{
        TSPInstance::solution solution = getNewSolution(currSolution, move);
        int res = Solver::calculateObjectiveFunction(solution, instance);
        return res;
    }
}

TSPInstance::solution Insert::getNewSolution(const TSPInstance::solution &old, const std::vector<int> &move) {
    std::vector<int> newSolution(old);
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
