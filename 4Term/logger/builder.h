#ifndef BUILDER_H
#define BUILDER_H
#include <iostream>
#include <memory>
#include "logger.h"

class builder
{
public:
    virtual builder* add_stream(std::string const &target, fund_alg::logger::severity level) = 0;

    virtual std::shared_ptr<fund_alg::logger> build() const = 0;

    virtual ~builder() = default;
};

#endif //BUILDER_H