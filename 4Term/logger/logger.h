#ifndef LOGGER_H
#define LOGGER_H
#include <iostream>
#include "namespace.h"

class fund_alg::logger
{
public:
    enum class severity
    {
        trace,
        debug,
        information,
        warning,
        error,
        critical
    };

    virtual fund_alg::logger const * log(const std::string &message, severity level) const = 0;

    virtual ~logger() = default;
};

#endif // LOGGER_H