#include "ProblemFactory.h"
#include <stdlib.h>
#include "../util.h"
std::shared_ptr<Euc2DInstance> ProblemFactory::createEuc2DInstance(unsigned int range, unsigned int size, const std::string& name)
{
    auto instance = std::make_shared<Euc2DInstance>(size);
    
    instance->setName(name != "" ? name : ("RANDOM_EUC2D_" + std::to_string(util::random(int_limit))));
    auto v = std::vector<std::pair<int, int>>(size);
    for (int i = 0; i < size; i ++)
        v[i] = std::pair<int, int>(util::random(range), util::random(range)); 
    instance->setCoords(v);

    return instance;
}

std::shared_ptr<MatrixInstance> ProblemFactory::createMatrixInstance(unsigned int maxDistance, unsigned int size, const std::string& name)
{
    auto instance = std::make_shared<MatrixInstance>(size);
    
    instance->setName(name != "" ? name : ("RANDOM_MATIRX_" + std::to_string(util::random(int_limit))));
    auto v = std::vector<std::vector<int>>(size, std::vector<int>(size));
    for (int i = 0; i < size; i ++){
        for (int j = 0; j < size; j++) {
            v[i][j] = (i == j? MatrixInstance::infty : util::random(maxDistance));
        }
    }
    instance->setMatrix(v);

    return instance;
}