#ifndef LOGGER_H
#define LOGGER_H
#include <iostream>
#include <map>

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

    virtual logger const *log(const std::string &message, severity level) const = 0;

    virtual ~logger() {};
};

#endif // LOGGER_H