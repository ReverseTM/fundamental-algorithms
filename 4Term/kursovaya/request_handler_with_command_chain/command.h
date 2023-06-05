#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include <vector>
#include <sstream>
#include "../memory_allocators/memory.h"
#include "../types/data_type.h"
#include "../validate/digit_validator.h"
#include "../validate/date_validator.h"
#include "../validate/time_validator.h"

class command
{

public:

    virtual ~command() = default;

protected:

    std::vector<std::string> split(std::string const & text, char delim) const;

public:

    virtual bool can_execute(std::string const &) noexcept = 0;

    virtual void execute(std::string const &) const noexcept = 0;
};

#endif //COMMAND_H
