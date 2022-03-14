#ifndef __EUC2DINSTANCE_H__
#define __EUC2DINSTANCE_H__

#include "TSPInstance.h"
#include <iostream>

class Euc2DInstance : public TSPInstance {
    std::vector<std::pair<int, int>> coords; 

    std::ostream& format(std::ostream& out) const override;
public:
    Euc2DInstance(int size);

    int getCost(const int& a, const int& b) override;
    
    void setCoords(const std::vector<std::pair<int, int >>& coords);
    std::pair<int, int> getCoords(const int& i) const;
};

#endif // __EUC2DINSTANCE_H__