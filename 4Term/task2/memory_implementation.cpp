#include "memory_implementation.h"

void *Memory_implementation::allocate(const Logger &logger, size_t target_size) const
{
    logger.log("Memory allocated", Logger::severity::trace);
    return reinterpret_cast<void*>(new unsigned char[target_size]);
}

void Memory_implementation::deallocate(const Logger &logger, void const *target_to_dealloc) const
{
    logger.log("Memory deallocate", Logger::severity::trace);
    delete[] target_to_dealloc;
}