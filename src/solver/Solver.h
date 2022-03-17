#ifndef __SOLVER_H__
#define __SOLVER_H__

#include "../tsp_data/TSPInstance.h"
#include <memory>

class Solver {
    virtual TSPInstance::solution solve(std::shared_ptr<TSPInstance> instance) = 0;
};

#endif // __SOLVER_H__