#ifndef JSON_H
#define JSON_H
#include "forJson/single_include/nlohmann/json.hpp"
#include "logger.h"

class Json
{
public:
    virtual Logger* create() const = 0;

    virtual ~Json() = default;
};

#endif //JSON_H
