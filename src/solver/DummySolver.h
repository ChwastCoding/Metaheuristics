#ifndef __DUMMYSOLVER_H__
#define __DUMMYSOLVER_H__

#include "Solver.h"
#include <chrono>

class DummySolver : public Solver {
    std::chrono::time_point<std::chrono::high_resolution_clock> previous, current;
public:
    DummySolver(std::shared_ptr<TSPInstance> instance);
    void step() override;
};

#endif // __DUMMYSOLVER_H__