#ifndef LOGGER_H
#define LOGGER_H
#include <iostream>
#include <map>
#include <ctime>

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

    virtual logger const *log(const std::string&, severity) const = 0;

    virtual ~logger() {};
};


#endif // LOGGER_H
