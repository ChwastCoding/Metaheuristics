#ifndef __DUMMYSOLVER_H__
#define __DUMMYSOLVER_H__

#include "Solver.h"

class DummySolver : public Solver {
private:
    TSPInstance::solution cachedSolution;
public:
    TSPInstance::solution solve(std::shared_ptr<TSPInstance> instance) override;
};

#endif // __DUMMYSOLVER_H__