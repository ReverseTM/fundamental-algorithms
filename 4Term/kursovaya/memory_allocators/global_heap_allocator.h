#ifndef GLOBAL_HEAP_MEMORY_H
#define GLOBAL_HEAP_MEMORY_H
#include "memory.h"
#include "memory_holder.h"
#include "../logger/logger_implementation.h"
#include "../logger/builder_implementation.h"
#include "../logger/json_implementation.h"
#include "../logger/logger_holder.h"

class global_heap_allocator final :
        public memory,
        public logger_holder,
        public memory_holder
{
private:

    logger *_log_memory = nullptr;

public:

    void * const allocate(size_t target_size) const override;

    void deallocate(void * target_to_dealloc) const override;

    global_heap_allocator(logger * const log_memory);

public:

    global_heap_allocator(global_heap_allocator const & other) = delete;

    global_heap_allocator & operator=(global_heap_allocator const & other) = delete;

    global_heap_allocator(global_heap_allocator && other) = delete;

    global_heap_allocator & operator=(global_heap_allocator && other) = delete;

protected:

    size_t get_occupied_block_size_without_service_block(void *current_block) const override;

    void * get_address_relative_to_allocator(void * current_block_address) const override;

    logger * get_logger() const override;

    memory * get_outer_allocator() const override;
};


#endif //GLOBAL_HEAP_MEMORY_H
