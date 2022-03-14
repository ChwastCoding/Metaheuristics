#include "Euc2DInstance.h"
#include <math.h>

int Euc2DInstance::getCost(const int& a, const int& b)
{
    auto a_coord = coords[a], b_coord = coords[b];
    auto x = a_coord.first - b_coord.first;
    auto y = a_coord.second - b_coord.second;
    return sqrt(x*x + y*y);
}

void Euc2DInstance::setCoords(const std::vector<std::pair<int, int >>& coords)
{
    this->coords = coords;
}

std::pair<int, int> Euc2DInstance::getCoords(const int& i) const
{
    return coords[i];
}

// Euc2DInstance::Euc2DInstance(int size) : TSPInstance(size) {}

std::ostream& Euc2DInstance::format(std::ostream& out) const 
{
    out << "NAME : " << name << "\n";
    out << "TSP : TSP\n";
    out << "DIMENSION : " << size << "\n";
    out << "EDGE_WEIGHT_TYPE: EUC_2D\n";
    out << "NODE_COORD_SECTION\n";
    for (int i = 0; i < size; i ++) {
        out << i + 1 << " " << coords[i].first << " " << coords[i].second << "\n";
    }
    out << "EOF" << std::endl;
    return out;
}

Euc2DInstance::Euc2DInstance(int size) : TSPInstance(size) {}
