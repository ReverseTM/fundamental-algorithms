#ifndef BUILDER_H
#define BUILDER_H
#include <iostream>
#include "logger.h"

class Builder
{
public:
    virtual Builder* add_stream(std::string const &target, Logger::severity level) = 0;

    virtual Logger* build() const = 0;

    virtual ~Builder() = default;
};

#endif //BUILDER_H