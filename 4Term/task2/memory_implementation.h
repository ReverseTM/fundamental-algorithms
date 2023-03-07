#ifndef MEMORY_IMPLEMENTATION_H
#define MEMORY_IMPLEMENTATION_H
#include "memory.h"

class Memory_implementation final : public Memory
{
public:
    void *allocate(const Logger &logger, size_t target_size) const override;

    void deallocate(const Logger &logger, void const *target_to_dealloc) const override;
};


#endif //MEMORY_IMPLEMENTATION_H
