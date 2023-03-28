#ifndef MEMORY_H
#define MEMORY_H
#include <iostream>
#include "../logger/logger.h"

class memory {

public:

    friend void *const operator +=(memory const &allocator, size_t target_size);
    friend void operator -=(memory const &allocator, void *const target_to_dealloc);

public:

    class memory_exception final : public std::exception
    {
    private:

        std::string _msg;

    public:

        const char *what() const noexcept override;

        memory_exception(const std::string &msg);

    };

public:

    enum class allocation_mode
    {
        first_match,
        the_best_match,
        the_worst_match
    };

public:

    virtual void *const allocate(size_t target_size) const = 0;

    virtual void deallocate(void * target_to_dealloc) const = 0;

    virtual ~memory() = default;

protected:

    virtual size_t get_available_block_service_block_size() const;

    virtual size_t get_occupied_block_service_block_size() const;

    virtual size_t get_allocator_service_block_size() const;

    virtual size_t get_allocated_memory_size() const;

    virtual size_t get_available_block_size(void *current_block) const;

    virtual size_t get_occupied_block_size(void *current_block) const;

    virtual memory* get_outer_allocator() const;

    virtual fund_alg::logger* get_logger() const;

    virtual memory::allocation_mode get_allocation_mode() const;

    virtual void* get_first_available_block() const;

    virtual void** get_first_available_block_ptr() const;

    virtual void* get_next_available_block(void *current_block) const;

    virtual void memory_state_before_deallocation(void * const block_of_memory) const;

    static std::string address_to_string(void const * const address);

};

#endif //MEMORY_H
