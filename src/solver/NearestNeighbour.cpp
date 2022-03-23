
#include "NearestNeighbour.h"
#include <bits/stdc++.h>

#include <utility>

NearestNeighbour::NearestNeighbour(std::shared_ptr<TSPInstance> instance, int startingPoint) : Solver(std::move(instance)) {
    this->startingPoint = startingPoint;
    setupUnvisitedNodes();
    solution.push_back(startingPoint);
    std::remove(unvisited.begin(), unvisited.end(), startingPoint);
}

void NearestNeighbour::setupUnvisitedNodes() {
    unvisited.resize(instance->getSize());
    for(int i = 0; i < instance->getSize(); i++){
        unvisited[i] = i;
    }
}

bool NearestNeighbour::step() {
    if(unvisited.empty()) return false;
    if (std::chrono::duration_cast<std::chrono::milliseconds>(current - previous).count() > 100) {
        previous = current;
        int nearestNeighbour = getNearestNeighbour();
        solution.push_back(nearestNeighbour);
        std::remove(unvisited.begin(), unvisited.end(), nearestNeighbour);
    }
    current = std::chrono::high_resolution_clock::now();
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
