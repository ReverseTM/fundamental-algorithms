#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>

class logger
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

    virtual logger const * log(const std::string &message, severity level) const = 0;

    virtual ~logger() = default;
};

#endif // LOGGER_H