#ifndef PROJECT_SORTED_LIST_MEMORY_H
#define PROJECT_SORTED_LIST_MEMORY_H
#include "memory.h"
#include "../logger/logger_implementation.h"
#include "../logger/builder_implementation.h"
#include "../logger/json_implementation.h"

class sorted_list_allocator final : public memory
{
private:

    void *_allocated_memory;

public:

    void *const allocate(size_t target_size) const override;

    void deallocate(void * target_to_dealloc) const override;

    sorted_list_allocator const *log_with_guard(const std::string&, fund_alg::logger::severity) const;

    explicit sorted_list_allocator(
            size_t target_size,
            memory::allocation_mode mode = memory::allocation_mode::first_match,
            fund_alg::logger *logger = nullptr,
            memory *outer_allocator = nullptr
                    );

    ~sorted_list_allocator() override;

protected:

    size_t get_available_block_service_block_size() const override;

    size_t get_occupied_block_service_block_size() const override;

    size_t get_allocator_service_block_size() const override;

    size_t get_allocated_memory_size() const override;

    size_t get_available_block_size(void *current_block) const override;

    size_t get_occupied_block_size(void *current_block) const override;

    memory* get_outer_allocator() const override;

    fund_alg::logger* get_logger() const override;

    memory::allocation_mode get_allocation_mode() const override;

    void* get_first_available_block() const override;

    void **get_first_available_block_ptr() const override;

    void* get_next_available_block(void *current_block) const override;

    void memory_state_before_deallocation(void * const block_of_memory) const override;

};


#endif //PROJECT_SORTED_LIST_MEMORY_H
