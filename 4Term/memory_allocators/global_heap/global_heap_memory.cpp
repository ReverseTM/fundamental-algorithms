#include "global_heap_memory.h"

global_heap_allocator::global_heap_allocator(const fund_alg::logger * const log_memory)
    : _log_memory(log_memory) {}

void global_heap_allocator::memory_state_before_deallocation(void * const block_of_memory) const
{
    size_t block_size = *(reinterpret_cast<size_t *>(block_of_memory));
    auto *iter = reinterpret_cast<unsigned char*>(block_of_memory);
    std::string bytes;

    for(size_t i = 0; i < block_size; i++)
    {
        bytes += std::to_string(static_cast<unsigned short>(*iter++));

        if (i != block_size - 1)
        {
            bytes += ' ';
        }
    }
    _log_memory->log("Memory state at address: " + address_to_string(block_of_memory) + " = [" + bytes + "]", fund_alg::logger::severity::trace);
}

void * const global_heap_allocator::allocate(size_t target_size) const
{
    try
    {
        auto *block_of_memory = ::operator new(target_size + sizeof(size_t));

        auto *block_size = reinterpret_cast<size_t*>(block_of_memory);
        *block_size = target_size;

        auto * available_block = reinterpret_cast<void*>(block_size + 1);

        _log_memory->log("[GLOBAL HEAP]Memory allocated success at address: " + address_to_string(block_of_memory), fund_alg::logger::severity::trace);

        return available_block;
    }
    catch (const std::bad_alloc &ex)
    {
        throw memory_exception("Memory allocated error! \n");
    }
}

void global_heap_allocator::deallocate(void *const target_to_dealloc) const
{
    auto * block_of_memory = reinterpret_cast<void*>(reinterpret_cast<size_t*>(const_cast<void*>(target_to_dealloc)) - 1);

    memory_state_before_deallocation(target_to_dealloc);

    std::string address = address_to_string(block_of_memory);

    ::operator delete(block_of_memory);

    _log_memory->log("[GLOBAL HEAP]Memory at address: " + address + " was deallocated!", fund_alg::logger::severity::trace);
}

void *const operator+=(memory const &allocator, size_t target_size)
{
    return allocator.allocate(target_size);
}

void operator-=(memory const &allocator, void *const target_to_dealloc)
{
    allocator.deallocate(target_to_dealloc);
}