#ifndef __MATRIXINSTANCE_H__
#define __MATRIXINSTANCE_H__

#include "TSPInstance.h"
#include <iostream>

class MatrixInstance : public TSPInstance {
    std::ostream& format(std::ostream& out) const override;

    std::vector<std::vector<int>> matrix;
    bool isSymetric;
public:
    static const int infty = 9999;

    enum MatrixType {
        UNDEFINED,
        FULL,
        UPPER_ROW,
        LOWER_ROW,
        UPPER_COL,
        LOWER_COL,
        UPPER_DIAG_ROW,
        LOWER_DIAG_ROW,
        UPPER_DIAG_COL,
        LOWER_DIAG_COL
    };

    MatrixInstance(int size);

    void setMatrix(const std::vector<std::vector<int>>& matrix);
    void setType(MatrixType type);
    void setIsSymetric(bool s);

    int getCost(const int& a, const int& b) override;
private:
    MatrixType matrixType;
};

#endif // __MATRIXINSTANCE_H__