
#include "NearestNeighbour.h"
#include <bits/stdc++.h>

#include <utility>

NearestNeighbour::NearestNeighbour(std::shared_ptr<TSPInstance> instance, int startingPoint) : Solver(std::move(instance)) {
    this->startingPoint = startingPoint;
    setupUnvisitedNodes();
    solution.push_back(startingPoint);
    std::remove(unvisited.begin(), unvisited.end(), startingPoint);
    unvisited.pop_back();
}

void NearestNeighbour::setupUnvisitedNodes() {
    unvisited.resize(instance->getSize());
    for(int i = 0; i < instance->getSize(); i++){
        unvisited[i] = i;
    }
}

bool NearestNeighbour::step() {
    if(unvisited.empty()) return false;
    int nearestNeighbour = getNearestNeighbour();
    solution.push_back(nearestNeighbour);
    std::remove(unvisited.begin(), unvisited.end(), nearestNeighbour);
    unvisited.pop_back();
    return true;
}

int NearestNeighbour::getNearestNeighbour(){
    int min_dist = INT_MAX;
    int nearestNeighbour;
    int currNode = solution[solution.size()-1];
    for(int & i : unvisited){
        if(instance->getCost(currNode, i) < min_dist){
            nearestNeighbour = i;
            min_dist = instance->getCost(currNode, i);
        }
    }
    return nearestNeighbour;
}

void  NearestNeighbour::iterate() {
    while(step());
}
