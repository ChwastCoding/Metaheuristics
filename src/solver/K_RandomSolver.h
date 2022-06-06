#ifndef METAHEURISITICS_K_RANDOMSOLVER_H
#define METAHEURISITICS_K_RANDOMSOLVER_H

#include "DummySolver.h"
#include "Solver.h"
#include <random>
#include <algorithm>

class K_RandomSolver : public Solver{
    protected:
        std::chrono::time_point<std::chrono::high_resolution_clock> previous, current;
        int k;
        std::default_random_engine rng;
        TSPInstance::solution currSolution;
    public:
        bool step() override;
        void setSolution(const TSPInstance::solution& solution);
        void setupInitialCurrSolution();
        K_RandomSolver(std::shared_ptr<TSPInstance> instance, int k);
};

#endif //METAHEURISITICS_K_RANDOMSOLVER_H
