#ifndef MEMORY_H
#define MEMORY_H
#include <iostream>
#include "../task1/logger_implementation.h"
#include "../task1/json_implementation.h"

class Memory
{
public:
    virtual void *allocate(const Logger &logger, size_t target_size) const = 0;

    virtual void deallocate(const Logger &logger, void const *target_to_dealloc) const = 0;

    virtual ~Memory() = default;
};

#endif //MEMORY_H
