#include "global_heap_allocator.h"

global_heap_allocator::global_heap_allocator(const fund_alg::logger * const log_memory)
    : _log_memory(log_memory) {}

void global_heap_allocator::memory_state_before_deallocation(void * const block_of_memory) const
{
    size_t block_size = *(reinterpret_cast<size_t *>(block_of_memory) - 1);
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
    _log_memory->log("[GLOBAL HEAP ALLOCATOR] Memory state at address: " + address_to_string(block_of_memory) + " = [" + bytes + "]", fund_alg::logger::severity::trace);
}

void * const global_heap_allocator::allocate(size_t target_size) const
{
    try
    {
        auto *block_of_memory = ::operator new(target_size + sizeof(size_t));

        auto *block_size = reinterpret_cast<size_t*>(block_of_memory);
        *block_size = target_size;


        _log_memory->log("[GLOBAL HEAP ALLOCATOR] Memory allocated success at address: " + address_to_string(block_size + 1) + " success.", fund_alg::logger::severity::trace);

        return reinterpret_cast<void*>(block_size + 1);
    }
    catch (const std::bad_alloc &ex)
    {
        std::string message = "Memory allocated error";
        _log_memory->log("[GLOBAL HEAP ALLOCATOR] " + message + ".", fund_alg::logger::severity::warning);

        throw memory_exception("Memory allocated error");
    }
}

void global_heap_allocator::deallocate(void * target_to_dealloc) const
{
    memory_state_before_deallocation(target_to_dealloc);

    auto * target_block = reinterpret_cast<void*>(reinterpret_cast<size_t*>(target_to_dealloc) - 1);

    ::operator delete(target_block);

    _log_memory->log("[GLOBAL HEAP ALLOCATOR] Memory at address: " + address_to_string(target_to_dealloc) + " was deallocated.", fund_alg::logger::severity::trace);
}

void *const operator+=(memory const &allocator, size_t target_size)
{
    return allocator.allocate(target_size);
}

void operator-=(memory const &allocator, void *const target_to_dealloc)
{
    allocator.deallocate(target_to_dealloc);
}