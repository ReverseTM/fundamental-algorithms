#include "memory_implementation.h"


void *memory_implementation::allocate(size_t target_size) const
{
    return static_cast<void*>(new unsigned char[target_size]);
}

void memory_implementation::deallocate(void const *target_to_dealloc) const
{
    delete target_to_dealloc;
}