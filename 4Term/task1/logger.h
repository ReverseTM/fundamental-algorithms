#ifndef LOGGER_H
#define LOGGER_H
#include <iostream>
#include <map>

class Logger
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

    virtual Logger const *log(const std::string &message, severity level) const = 0;

    virtual ~Logger() = default;
};

#endif // LOGGER_H