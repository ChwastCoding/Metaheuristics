#include "TSPInstance.h"

std::ostream& operator<< (std::ostream& out, const TSPInstance& instance)
{
    return instance.format(out);    
}
std::string TSPInstance::getName() const
{
    return name;
}

void TSPInstance::setName(const std::string& name)
{
    this->name = name;
}

int TSPInstance::getSize() const
{
    return size;
}

bool TSPInstance::getIsSymetric() const
{
    return isSymetric;
}

void TSPInstance::setIsSymetric(bool s)
{
    isSymetric = s;
}