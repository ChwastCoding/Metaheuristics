
#include "NearestNeighbour.h"
#include <bits/stdc++.h>


NearestNeighbour::NearestNeighbour(const std::shared_ptr<TSPInstance>& instance, int startingPoint) : Solver(instance), unvisited(instance->getSize()) {
    this->startingPoint = startingPoint;
    std::iota(unvisited.begin(),unvisited.end(), 0);
    solution.push_back(startingPoint);
    std::remove(unvisited.begin(), unvisited.end(), startingPoint);
    unvisited.pop_back();
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