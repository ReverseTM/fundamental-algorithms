#ifndef GLOBAL_HEAP_MEMORY_H
#define GLOBAL_HEAP_MEMORY_H
#include "memory.h"
#include "../logger/logger_implementation.h"
#include "../logger/builder_implementation.h"
#include "../logger/json_implementation.h"

class global_heap_allocator final : public memory
{
private:

    const fund_alg::logger *_log_memory = nullptr;

public:

    void *const allocate(size_t target_size) const override;

    void deallocate(void * target_to_dealloc) const override;

    global_heap_allocator(const fund_alg::logger * const log_memory);

private:

    void memory_state_before_deallocation(void * const block_of_memory) const override;

};


#endif //GLOBAL_HEAP_MEMORY_H
