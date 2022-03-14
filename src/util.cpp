#include "util.h"

namespace util
{
    std::string trimWhitespace(const std::string& s)
    {
        std::size_t i = s.size();
        while (i && s[i - 1] == ' ') i--;
        return s.substr(0, i);
    }   
} // namespace util
