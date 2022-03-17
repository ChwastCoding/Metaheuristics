#ifndef __UTIL_H__
#define __UTIL_H__

#include <string>
#include <vector>

typedef std::vector<std::pair<int, int>> IntPairVec; 

namespace util
{
    std::string trimWhitespace(const std::string& s);
    
    char* getCmdOption(int argc, char** argv,  const std::string& option);
    
    bool cmdOptionExists(int argc, char** argv, const std::string& option);

} // namespace util

#endif // __UTIL_H__