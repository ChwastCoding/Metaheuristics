#include "ProblemFactory.h"
#include <stdlib.h>

inline int ProblemFactory::random(int a, int b)
{
    return rand() % (b - a) + a;
}

inline int ProblemFactory::random(int range)
{
    return random(0, range);
}

void ProblemFactory::initPRNG(unsigned int seed)
{
    srand(seed);
}

std::shared_ptr<Euc2DInstance> ProblemFactory::createEuc2DInstance(unsigned int range, unsigned int size, const std::string& name)
{
    auto instance = std::make_shared<Euc2DInstance>(size);
    
    instance->setName(name != "" ? name : ("RANDOM_EUC2D_" + std::to_string(random(int_limit))));
    auto v = std::vector<std::pair<int, int>>(size);
    for (int i = 0; i < size; i ++)
        v[i] = std::pair<int, int>(random(range), random(range)); 
    instance->setCoords(v);

    return instance;
}

std::shared_ptr<MatrixInstance> ProblemFactory::createMatrixInstance(unsigned int maxDistance, unsigned int size, const std::string& name)
{
    auto instance = std::make_shared<MatrixInstance>(size);
    
    instance->setName(name != "" ? name : ("RANDOM_MATIRX_" + std::to_string(random(int_limit))));
    auto v = std::vector<std::vector<int>>(size, std::vector<int>(size));
    for (int i = 0; i < size; i ++){
        for (int j = 0; j < size; j++) {
            v[i][j] = (i == j? MatrixInstance::infty : random(maxDistance));
        }
    }
    instance->setMatrix(v);

    return instance;
}