#include "memory.h"
#include "../logger/logger.h"
#include <sstream>

memory::memory_exception::memory_exception(const std::string &msg)
    : _msg(msg) {}

const char *memory::memory_exception::what() const noexcept
{
    return _msg.c_str();
}

std::string memory::address_to_string(const void * const address)
{
    return std::string { (std::stringstream () << address).str() };
}

size_t memory::get_available_block_service_block_size() const
{
    throw memory::memory_exception("Method not implemented");
}

size_t memory::get_occupied_block_service_block_size() const
{
    throw memory::memory_exception("Method not implemented");
}
size_t memory::get_allocator_service_block_size() const
{
    throw memory::memory_exception("Method not implemented");
}

size_t memory::get_allocated_memory_size() const
{
    throw memory::memory_exception("Method not implemented");
}

size_t memory::get_available_block_size(void *current_block) const
{
    throw memory::memory_exception("Method not implemented");
}

size_t memory::get_occupied_block_size(void *current_block) const
{
    throw memory::memory_exception("Method not implemented");
}

memory* memory::get_outer_allocator() const
{
    throw memory::memory_exception("Method not implemented");
}

fund_alg::logger* memory::get_logger() const
{
    throw memory::memory_exception("Method not implemented");
}

memory::allocation_mode memory::get_allocation_mode() const
{
    throw memory::memory_exception("Method not implemented");
}

void* memory::get_first_available_block() const
{
    throw memory::memory_exception("Method not implemented");
}

void** memory::get_first_available_block_ptr() const
{
    throw memory::memory_exception("Method not implemented");
}

void* memory::get_next_available_block(void *current_block) const
{
    throw memory::memory_exception("Method not implemented");
}

void memory::memory_state_before_deallocation(void * const block_of_memory) const
{
    throw memory::memory_exception("Method not implemented");
}