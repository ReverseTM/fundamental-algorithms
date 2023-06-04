#ifndef COMMAND_H
#define COMMAND_H

#include <iostream>
#include "../memory_allocators//memory.h"

class command
{

public:

    virtual ~command() = default;

public:

    virtual bool can_execute(std::string const &) const noexcept = 0;

    virtual void execute(std::string const &) const noexcept = 0;
};

#endif //COMMAND_H
