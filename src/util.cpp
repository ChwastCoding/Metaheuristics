#include "util.h"
#include <algorithm>
#include <sstream>

namespace util
{
    std::string trimWhitespace(const std::string& s)
    {
        auto copy = s.substr(s.find_first_not_of(" "));
        std::size_t i = copy.size();
        while (i && copy[i - 1] == ' ') i--;
        return copy.substr(0, i);
    }
    
    char* getCmdOption(int argc, char** argv, const std::string& option)
    {
        char** end = argc + argv;
        char** itr = std::find(argv, end, option);
        if (itr != end && ++itr != end) {
            return *itr;
        }
        return 0;
    }
    
    bool cmdOptionExists(int argc, char** argv, const std::string& option)
    {
        return std::find(argv, argc + argv, option) != argc + argv;
    }
} // namespace util
