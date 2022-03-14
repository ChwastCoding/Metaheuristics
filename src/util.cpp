#include "util.h"

namespace util
{
    std::string trimWhitespace(const std::string& s)
    {
        auto copy = s.substr(s.find_first_not_of(" "));
        std::size_t i = copy.size();
        while (i && copy[i - 1] == ' ') i--;
        return copy.substr(0, i);
    }   
} // namespace util
