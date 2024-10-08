#ifndef BORDER_DESCRIPTORS_ALLOCATOR_H
#define BORDER_DESCRIPTORS_ALLOCATOR_H
#include "memory.h"
#include "memory_holder.h"
#include "../logger/logger_implementation.h"
#include "../logger/builder_implementation.h"
#include "../logger/json_implementation.h"
#include "../logger/logger_holder.h"


class border_descriptors_allocator final :
        public memory,
        public logger_holder,
        public memory_holder
{
private:

    void * _allocated_memory;

public:

    void * const allocate(size_t target_size) const override;

    void deallocate(void * target_to_dealloc) const override;

    explicit border_descriptors_allocator(
            size_t target_size,
            memory::allocation_mode mode,
            logger *logger = nullptr,
            memory *outer_allocator = nullptr
            );

    ~border_descriptors_allocator() override;

public:

    border_descriptors_allocator(border_descriptors_allocator const & other) = delete;

    border_descriptors_allocator & operator=(border_descriptors_allocator const & other) = delete;

    border_descriptors_allocator(border_descriptors_allocator && other) = delete;

    border_descriptors_allocator & operator=(border_descriptors_allocator && other) = delete;

protected:

    size_t get_allocator_service_block_size() const override; //

    size_t get_allocated_memory_size() const override; //

    void * get_start_allocated_memory_address() const override;

    void * get_end_allocated_memory_address() const override;

    size_t get_available_block_size(void * next_occupied_block_to_target_block) const override; //

    size_t get_occupied_block_service_block_size() const override; //

    size_t get_occupied_block_size(void * current_block) const override; //

    size_t get_occupied_block_size_without_service_block(void * current_block) const override; //

    void * get_first_occupied_block() const override; //

    void ** get_first_occupied_block_ptr() const override; //

    void * get_next_occupied_block(void * current_block) const; //

    void * get_previous_occupied_block(void * current_block) const; //

    void * get_address_relative_to_allocator(void * current_block_address) const override;

    memory* get_outer_allocator() const override; //

    logger * get_logger() const override; //

    memory::allocation_mode get_allocation_mode() const override; //

};


#endif //BORDER_DESCRIPTORS_ALLOCATOR_H
