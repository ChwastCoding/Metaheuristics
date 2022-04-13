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
    int calculateObjectiveFunction(const TSPInstance::solution& solution);
    virtual int calculateObjectiveFunction();
    static int calculateObjectiveFunction(const TSPInstance::solution& solution, const std::shared_ptr<TSPInstance> instance);
};

#endif // __SOLVER_H__