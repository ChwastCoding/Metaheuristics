#include "TwoOptSolver.h"

#include <algorithm>
#include "../util.h"
#include <iostream>
#include "NearestNeighbour.h"

TwoOptSolver::TwoOptSolver(std::shared_ptr<TSPInstance> instance, bool NN_mode, Mode mode_)
: Solver(instance), mode(mode_) {
    if (NN_mode) {
        NearestNeighbour nn(instance, 0);
        while (nn.step());
        solution = nn.getSolution();
    } else{
        setupInitialSolution();
    } 
    currentObjective = Solver::calculateObjectiveFunction(solution);

    size = solution.size();
    if (mode == Mode::LOOK_UP) {
        lookUp = std::vector<std::vector<int>> (size);
        for (int i = 0; i < size; i ++) {
            lookUp[i] = std::vector<int>(size - i, 0);
            for (int j = i + 1; j < size; j ++) {
                lookUp[i][j - i] = instance->getCost(i, j);
            }
        }
    }
}

bool TwoOptSolver::step() {
    if (instance->getIsSymetric()) {
        switch (mode) {
        case Mode::RUNTIME: return symetricRunTimeStep();
        case Mode::LOOK_UP: return symetricLookUpStep();
        case Mode::NAIVE: return symetricNaiveStep();
        }
    }
    return asymetricStep();
}

int TwoOptSolver::calculateObjectiveFunction()
{
    return currentObjective;
}

void TwoOptSolver::setSolution(TSPInstance::solution& s)
{
    solution = s;
    currentObjective = Solver::calculateObjectiveFunction(solution, instance);
}

bool TwoOptSolver::symetricNaiveStep()
{
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size && !(i == 0 && j == size - 1); j ++) {
            auto copy = TSPInstance::solution(solution.begin(), solution.end());
            std::reverse(copy.begin() + i, copy.begin() + j + 1);
            int res = Solver::calculateObjectiveFunction(copy);

            if (res < currentObjective) {
                solution = copy;
                currentObjective = res;
                return true;
            }
        }
    }
    return false;
}

bool TwoOptSolver::symetricLookUpStep()
{
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size && !(i == 0 && j == size - 1); j ++) {
            int res = currentObjective - lookUpCost(i - 1, i) - lookUpCost(j, j + 1)
                + lookUpCost(i - 1, j) + lookUpCost(i, j + 1);
            if (res < currentObjective) {
                std::reverse(solution.begin() + i, solution.begin() + j + 1);
                currentObjective = res;
                return true;
            }
        }
    }
    return false;
}

bool TwoOptSolver::symetricRunTimeStep()
{
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size && !(i == 0 && j == size - 1); j ++) {
            int res = currentObjective - runTimeCost(i - 1, i) - runTimeCost(j, j + 1)
                + runTimeCost(i - 1, j) + runTimeCost(i, j + 1);
            if (res < currentObjective) {
                std::reverse(solution.begin() + i, solution.begin() + j + 1);
                currentObjective = res;
                return true;
            }
        }
    }
    return false;
}

bool TwoOptSolver::asymetricStep()
{
    for (int i = 0; i < size; i ++) {
        for (int j = 0; j < size; j ++) {
            if (i == j) continue;
            auto copy = TSPInstance::solution(solution.begin(), solution.end());
            if (i < j) std::reverse(copy.begin() + i, copy.begin() + j + 1);
            else outerRotation(copy, i, j);

            int res = Solver::calculateObjectiveFunction(copy);
            if (res < currentObjective) {
                currentObjective = res;
                solution = copy;
                return true;
            }
        }
    }
    return false;
}

int TwoOptSolver::runTimeCost(int a, int b)
{
    return instance->getCost(solution[(size + a) % size], solution[(size + b) % size]);
}

int TwoOptSolver::lookUpCost(int a, int b)
{
    if (a < 0) a += solution.size();
    if (b >= solution.size()) b -= solution.size();
    a = solution[a];
    b = solution[b];
    return (a < b ? lookUp[a][b - a] : lookUp[b][a - b]);   
}

void TwoOptSolver::outerRotation(TSPInstance::solution& s, int a, int b)
{
    int c;
    do {
        std::swap(s[a], s[b]);
        c = a;
        if (++a == s.size()) a = 0;
        if (--b == -1) b = s.size() - 1;
    } while (c != b && b != a);
}
