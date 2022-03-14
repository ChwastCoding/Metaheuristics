#ifndef __PARSER_H__
#define __PARSER_H__

#include <string>
#include "TSPInstance.h"
#include <memory>

class Parser {
public:
    static std::shared_ptr<TSPInstance> getInstance(const std::string& path);
    static void saveInstance(std::shared_ptr<TSPInstance> instance, const std::string& path);
};

#endif // __PARSER_H__