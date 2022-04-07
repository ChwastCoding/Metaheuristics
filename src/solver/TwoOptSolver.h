#ifndef __TWOOPTSOLVER_H__
#define __TWOOPTSOLVER_H__

#include "Solver.h"

class TwoOptSolver : public Solver {
private:
    int currentObjective;

    bool symetricNaiveStep();
    bool symetricLookUpStep();
    bool symetricRunTimeStep();
    bool asymetricStep();

    int runTimeCost(int a, int b);
    int lookUpCost(int a, int b);

    void outerRotation(TSPInstance::solution& s, int a, int b);

    int size;
    std::vector<std::vector<int>> lookUp;

public:
    enum Mode {
        NAIVE,
        LOOK_UP,
        RUNTIME
    };

    TwoOptSolver(std::shared_ptr<TSPInstance> instance, bool NN_mode = false, Mode mode = LOOK_UP);
    
    bool step() override;
    int calculateObjectiveFunction() override;
private:
    Mode mode;
};

#endif // __TWOOPTSOLVER_H__