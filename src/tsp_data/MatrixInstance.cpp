#include "MatrixInstance.h"

MatrixInstance::MatrixInstance(int size) : TSPInstance(size) {}

void MatrixInstance::setMatrix(const std::vector<std::vector<int>>& matrix)
{
    this->matrix = matrix;
}

void MatrixInstance::setType(MatrixType type)
{
    this->matrixType = type;
}

void MatrixInstance::setIsSymetric(bool s)
{
    isSymetric = s;
}

int MatrixInstance::getCost(const int& a, const int& b)
{
    if (matrixType == MatrixType::FULL) return matrix[a][b];
    else return b >= a ? matrix[a][b - a] : matrix[b][a - b];
}

std::ostream& MatrixInstance::format(std::ostream& out) const 
{
    out << "NAME : " << name << "\n";
    out << "TYPE : " << (isSymetric ? "TSP" : "ATSP") << "\n";
    out << "DIMENSION : " << size << "\n";
    out << "EDGE_WEIGHT_TYPE: EXPLICIT\n";
    out << "EDGE_WEIGHT_FORMAT: " << (matrixType == MatrixType::FULL ? "FULL_MATRIX" : "UPPER_DIAG_ROW") << "\n";
    out << "EDGE_WEIGHT_SECTION\n";
    for (int i = 0; i < size; i ++) {
        for (int j = 0; j < matrix[i].size(); j ++) {
            out << " " << matrix[i][j];
        }
        out << "\n";
    } 
    out << "EOF\n";
    
    return out;
}
