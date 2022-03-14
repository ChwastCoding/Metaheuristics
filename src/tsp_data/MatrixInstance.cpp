#include "MatrixInstance.h"

MatrixInstance::MatrixInstance(int size) : TSPInstance(size) {}

void MatrixInstance::setMatrix(const std::vector<std::vector<int>>& matrix)
{
    this->matrix = matrix;
}

int MatrixInstance::getCost(const int& a, const int& b)
{
    return matrix[a][b];
}

std::ostream& MatrixInstance::format(std::ostream& out) const 
{
    out << "NAME : " << name << "\n";
    out << "TYPE : ATSP\n";
    out << "DIMENSION : " << size << "\n";
    out << "EDGE_WEIGHT_TYPE: EXPLICIT\n";
    out << "EDGE_WEIGHT_FORMAT: FULL_MATRIX\n";
    out << "EDGE_WEIGHT_SECTION\n";
    for (int i = 0; i < size; i ++) {
        for (int j = 0; j < size; j ++) {
            out << " " << matrix[i][j];
        }
        out << "\n";
    } 
    out << "EOF\n";
    
    return out;
}
