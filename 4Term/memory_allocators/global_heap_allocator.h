#ifndef GLOBAL_HEAP_MEMORY_H
#define GLOBAL_HEAP_MEMORY_H
#include "memory.h"
#include "../logger/logger_implementation.h"
#include "../logger/builder_implementation.h"
#include "../logger/json_implementation.h"

class global_heap_allocator final : public memory
{
private:

    fund_alg::logger *_log_memory = nullptr;

public:

    void * const allocate(size_t target_size) const override;

    void deallocate(void * target_to_dealloc) const override;

    global_heap_allocator(fund_alg::logger * const log_memory);

protected:

    size_t get_occupied_block_size_without_service_block(void *current_block) const override;

    void * get_address_relative_to_allocator(void * current_block_address) const override;

    fund_alg::logger * get_logger() const override;
};


#endif //GLOBAL_HEAP_MEMORY_H
