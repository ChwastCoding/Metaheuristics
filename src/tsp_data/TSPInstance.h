#ifndef __TSPINSTANCE_H__
#define __TSPINSTANCE_H__

#include <vector>
#include <string>

class TSPInstance {
protected:
    const int size;
    std::string name;
    TSPInstance(int size) : size(size) {};
    bool isSymetric;

    virtual std::ostream& format(std::ostream& out) const { return out; }
public:
    typedef std::vector<int> solution;

    std::string getName() const;
    void setName(const std::string& name);
    int getSize() const;
    bool getIsSymetric() const;
    void setIsSymetric(bool s);

    virtual int getCost(const int& a, const int& b) = 0;
    friend std::ostream& operator<< (std::ostream& out, const TSPInstance& instance);
};

#endif // __TSPINSTANCE_H__