#ifndef __PROBLEMFACTORY_H__
#define __PROBLEMFACTORY_H__

#include "Euc2DInstance.h"
#include "MatrixInstance.h"
#include <memory>
#include <limits>

class ProblemFactory {
    constexpr static int int_limit = std::numeric_limits<int>::max();

    inline static int random(int a, int b);
    inline static int random(int range);
public:
    static void initPRNG(unsigned int seed);
    static std::shared_ptr<Euc2DInstance> createEuc2DInstance(unsigned int range, unsigned int size, const std::string& name = "");
    static std::shared_ptr<MatrixInstance> createMatrixInstance(unsigned int maxDistance, unsigned int size, const std::string& name = "");
};

#endif // __PROBLEMFACTORY_H__