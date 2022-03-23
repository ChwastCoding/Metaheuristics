#ifndef __SOLVER_H__
#define __SOLVER_H__

#include "../tsp_data/TSPInstance.h"
#include <memory>

class Solver {
protected:
    std::shared_ptr<TSPInstance> instance;
    TSPInstance::solution solution;

    void setupInitialSolution();
public:
    Solver(std::shared_ptr<TSPInstance> instance);

    virtual bool step() = 0;

    TSPInstance::solution getSolution();
    virtual int calculateObjectiveFunction();
};

#endif // __SOLVER_H__