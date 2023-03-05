#ifndef MEMORY_IMPLEMENTATION_H
#define MEMORY_IMPLEMENTATION_H
#include "memory.h"

class memory_implementation final : public memory
{
public:
    void *allocate(size_t target_size) const override;

    void deallocate(void const *target_to_dealloc) const override;
};


#endif //MEMORY_IMPLEMENTATION_H
