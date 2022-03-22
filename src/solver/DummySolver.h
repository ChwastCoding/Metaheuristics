#ifndef __DUMMYSOLVER_H__
#define __DUMMYSOLVER_H__

#include "Solver.h"
#include <chrono>

class DummySolver : public Solver {
    std::chrono::time_point<std::chrono::high_resolution_clock> previous, current;
public:
    DummySolver(std::shared_ptr<TSPInstance> instance);
    
    // returns true while it's still working on the solution
    // and false when it's done solving the problem
    bool step() override;
    void setSolution(const TSPInstance::solution& solution);
};

#endif // __DUMMYSOLVER_H__