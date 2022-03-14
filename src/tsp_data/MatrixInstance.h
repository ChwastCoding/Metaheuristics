#ifndef __MATRIXINSTANCE_H__
#define __MATRIXINSTANCE_H__

#include "TSPInstance.h"
#include <iostream>

class MatrixInstance : public TSPInstance {
    std::ostream& format(std::ostream& out) const override;

    std::vector<std::vector<int>> matrix;
public:
    static const int infty = 9999;

    MatrixInstance(int size);

    void setMatrix(const std::vector<std::vector<int>>& matrix);

    int getCost(const int& a, const int& b) override;    
};

#endif // __MATRIXINSTANCE_H__