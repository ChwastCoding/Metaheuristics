#ifndef __UTIL_H__
#define __UTIL_H__

#include <string>
#include <vector>
#include <sstream>
#include <time.h>

typedef std::vector<std::pair<int, int>> IntPairVec;

namespace util
{
    inline void initializeRNG(uint seed) {
        srand(seed);
    }

    inline void initializeRNG() {
        srand(time(NULL));
    }

    inline int random(int a, int b) {
        return  std::rand() % (b - a) + a;
    }

    inline int random(int range) {
        return random(0, range);
    }

    inline float random() {
      return static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX);
    }

    std::string trimWhitespace(const std::string& s);

std::string getCmdOption(int argc, char** argv,  const std::string& option);

    bool cmdOptionExists(int argc, char** argv, const std::string& option);

    template<typename T> std::string toString(const std::vector<T>& v){
        if (v.empty()) return "[]";
        std::stringstream ss;
        ss << "[";
        for (int i = 0; i < v.size() - 1; i ++)
            ss << v[i] << ", ";
        ss << v[v.size() - 1] << "]";
        return ss.str();
    };

    template<typename A, typename B> std::string toStringPairVec(const std::vector<std::pair<A, B>>& v){
        if (v.empty()) return "[]";
        std::stringstream ss;
        for (int i = 0; i < v.size() - 1; i ++)
            ss << "(" << v[i].first << ", " << v[i].second << "), ";
        ss << "(" << v[v.size() -1].first << ", " << v[v.size() -1].second << ")]";
        return ss.str();
    };

} // namespace util

#endif // __UTIL_H__