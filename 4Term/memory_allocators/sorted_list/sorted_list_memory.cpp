#include "sorted_list_memory.h"

sorted_list_memory const *sorted_list_memory::log_with_guard(const std::string &message, fund_alg::logger::severity severity_level) const
{
    const fund_alg::logger *logger = get_logger();

    if (logger != nullptr)
    {
        logger->log(message, severity_level);
    }

    return this;
}

size_t sorted_list_memory::get_available_block_service_block_size() const
{
    return sizeof(size_t) + sizeof(void*);
}

size_t sorted_list_memory::get_occupied_block_service_block_size() const
{
    return sizeof(size_t);
}

size_t sorted_list_memory::get_allocator_service_block_size() const
{
    return sizeof(memory*) + sizeof(fund_alg::logger*) + sizeof(memory::allocation_mode) + sizeof(void*);
}

size_t sorted_list_memory::get_available_block_size(void *current_block) const
{
    return *reinterpret_cast<size_t*>(current_block);
}

size_t sorted_list_memory::get_occupied_block_size(void *current_block) const
{
    return *(reinterpret_cast<size_t*>(current_block) - 1);
}

fund_alg::logger* sorted_list_memory::get_logger() const
{
    return *reinterpret_cast<fund_alg::logger**>(reinterpret_cast<memory**>(_allocated_memory) + 1);
}

memory* sorted_list_memory::get_outer_allocator() const
{
    return *reinterpret_cast<memory**>(_allocated_memory);
}

memory::allocation_mode sorted_list_memory::get_allocation_mode() const
{
    return *reinterpret_cast<memory::allocation_mode*>(reinterpret_cast<fund_alg::logger**>(reinterpret_cast<memory**>(_allocated_memory) + 1) + 1);
}

void* sorted_list_memory::get_first_available_block() const
{
    return *reinterpret_cast<void**>(reinterpret_cast<memory::allocation_mode*>(reinterpret_cast<fund_alg::logger**>(reinterpret_cast<memory**>(_allocated_memory) + 1) + 1) + 1);
}

void** sorted_list_memory::get_first_available_block_ptr() const
{
    return reinterpret_cast<void**>(reinterpret_cast<memory::allocation_mode*>(reinterpret_cast<fund_alg::logger**>(reinterpret_cast<memory**>(_allocated_memory) + 1) + 1) + 1);
}

void* sorted_list_memory::get_next_available_block(void *current_block) const
{
    return *reinterpret_cast<void**>(reinterpret_cast<size_t*>(current_block) + 1);
}

void sorted_list_memory::memory_state_before_deallocation(void * const block_of_memory) const
{
    if (get_logger() == nullptr)
    {
        return;
    }

    auto const block_size = get_occupied_block_size(block_of_memory);
    auto * iter = reinterpret_cast<unsigned char*>(block_of_memory);

    std::string bytes;

    for(size_t i = 0; i < block_size; i++)
    {
        bytes += std::to_string(static_cast<unsigned short>(*iter++));

        if (i != block_size - 1)
        {
            bytes += ' ';
        }
    }

    this->log_with_guard("Memory state at address: " + address_to_string(block_of_memory) + " = [" + bytes + "]", fund_alg::logger::severity::trace);
}

sorted_list_memory::sorted_list_memory(
        size_t target_size,
        memory::allocation_mode mode,
        fund_alg::logger *logger,
        memory *outer_allocator
        )
{
    size_t allocator_service_block_size = get_allocator_service_block_size();

    if (target_size < allocator_service_block_size)
    {
        throw memory::memory_exception("Not enough memory!");
    }

    size_t memory_size = target_size + allocator_service_block_size;

    if (outer_allocator == nullptr)
    {
        _allocated_memory = ::operator new(memory_size);
    }
    else
    {
        _allocated_memory = outer_allocator->allocate(memory_size);
    }

    auto * const outer_allocator_ptr = reinterpret_cast<memory**>(_allocated_memory);
    *outer_allocator_ptr = outer_allocator;

    auto * const logger_ptr = reinterpret_cast<fund_alg::logger**>(outer_allocator_ptr + 1);
    *logger_ptr = logger;

    auto * const allocation_mode_ptr = reinterpret_cast<memory::allocation_mode*>(logger_ptr + 1);
    *allocation_mode_ptr = mode;

    auto * const first_available_block_ptr = reinterpret_cast<void**>(allocation_mode_ptr + 1);
    *first_available_block_ptr = reinterpret_cast<void*>(first_available_block_ptr + 1);

    auto * const first_available_block_size = reinterpret_cast<size_t*>(*first_available_block_ptr);
    *first_available_block_size = target_size;

    auto * const next_available_block_ptr = reinterpret_cast<void**>(first_available_block_size + 1);
    *next_available_block_ptr = nullptr;

    this->log_with_guard("Allocator with sorted list deallocation was successfully created", fund_alg::logger::severity::trace);

}

void * const  sorted_list_memory::allocate(size_t request_size) const
{
    void *previous_block = nullptr;
    void *target_block = nullptr;
    void *previous_to_target_block = nullptr;
    void *next_to_target_block = nullptr;
    auto current_block = get_first_available_block();
    auto available_block_service_block_size = get_available_block_service_block_size();
    auto occupied_block_service_block_size = get_occupied_block_service_block_size();
    auto allocation_mode = get_allocation_mode();

    while (current_block != nullptr)
    {
        auto current_block_size = get_available_block_size(current_block);
        auto next_block = get_next_available_block(current_block);

        if (current_block_size - available_block_service_block_size >= request_size + occupied_block_service_block_size)
        {
            if (
                    allocation_mode == memory::allocation_mode::first_match ||
                    allocation_mode == memory::allocation_mode::the_best_match && (target_block == nullptr || current_block_size < get_available_block_size(target_block)) ||
                    allocation_mode == memory::allocation_mode::the_worst_match && (target_block == nullptr || current_block_size > get_available_block_size(target_block))
                    )
            {
                previous_to_target_block = previous_block;
                target_block = current_block;
                next_to_target_block = next_block;
            }

            if (allocation_mode == memory::allocation_mode::first_match)
            {
                break;
            }
        }

        previous_block = current_block;
        current_block = next_block;
    }

    if (target_block == nullptr)
    {
        std::string message = "No available memory!";
        this->log_with_guard(message, fund_alg::logger::severity::trace);

        throw memory::memory_exception(message);
    }

    auto target_block_size = get_available_block_size(target_block);

    if (target_block_size - request_size - occupied_block_service_block_size <= available_block_service_block_size)
    {
        auto new_request_size = target_block_size - occupied_block_service_block_size - available_block_service_block_size;

        this->log_with_guard("Requested was " + std::to_string(request_size) + " bytes, but for correct operation " + std::to_string(new_request_size) + " were allocated", fund_alg::logger::severity::trace);

        request_size = new_request_size;
    }

    void * next_available_block_for_previous_block_ptr;

    if (request_size == target_block_size - occupied_block_service_block_size)
    {
        next_available_block_for_previous_block_ptr = next_to_target_block;
    }
    else
    {
        next_available_block_for_previous_block_ptr = reinterpret_cast<void*>(reinterpret_cast<unsigned char*>(target_block) + occupied_block_service_block_size + request_size);

        auto * const rest_part_of_block_size = reinterpret_cast<size_t*>(next_available_block_for_previous_block_ptr);
        *rest_part_of_block_size = target_block_size - request_size - occupied_block_service_block_size;

        auto * const next_block_to_rest_part_of_block = reinterpret_cast<void**>(rest_part_of_block_size + 1);
        *next_block_to_rest_part_of_block = next_to_target_block;
    }

    if (previous_to_target_block == nullptr)
    {
        auto * const first_available_block = get_first_available_block_ptr();
        *first_available_block = next_available_block_for_previous_block_ptr;
    }
    else
    {
        *reinterpret_cast<void**>(reinterpret_cast<size_t*>(previous_to_target_block) + 1) = next_available_block_for_previous_block_ptr;
    }

    auto *target_block_size_space = reinterpret_cast<size_t*>(target_block);
    *target_block_size_space = request_size;

    this->log_with_guard("[SORTED LIST]Memory allocation at address: " + address_to_string(target_block_size_space + 1) + " success!", fund_alg::logger::severity::trace);

    return reinterpret_cast<void*>(target_block_size_space + 1);
}

void sorted_list_memory::deallocate(void * const target_to_dealloc) const
{
    sorted_list_memory::memory_state_before_deallocation(target_to_dealloc);

    std::string address = address_to_string(target_to_dealloc);

    auto * target_block = const_cast<void*>(target_to_dealloc);
    target_block = reinterpret_cast<void*>(reinterpret_cast<size_t*>(target_block) - 1);

    auto available_block_service_block_size = get_available_block_service_block_size();
    auto occupied_block_service_block_size = get_occupied_block_service_block_size();
    void * previous_to_target_block = nullptr;
    auto next_to_target_block = get_first_available_block();

    while (next_to_target_block != nullptr && next_to_target_block < target_block)
    {
        previous_to_target_block = next_to_target_block;
        next_to_target_block = get_next_available_block(next_to_target_block);
    }

    auto target_block_size = get_available_block_size(target_block);
    auto * const next_available_block_to_target_block = reinterpret_cast<void**>(reinterpret_cast<size_t*>(target_block) + 1);

    if (next_to_target_block != nullptr &&
    reinterpret_cast<void*>(reinterpret_cast<unsigned char*>(target_block) + occupied_block_service_block_size + target_block_size) == next_to_target_block)
    {
        target_block_size += get_available_block_size(next_to_target_block);
        *next_available_block_to_target_block = get_next_available_block(next_to_target_block);
    }
    else
    {
        *next_available_block_to_target_block = next_to_target_block;
    }

    if (previous_to_target_block != nullptr &&
    reinterpret_cast<void*>(reinterpret_cast<unsigned char*>(previous_to_target_block) + available_block_service_block_size +
    get_available_block_size(previous_to_target_block)) == target_block)
    {
        auto * const previous_to_target_block_size_space = reinterpret_cast<size_t*>(previous_to_target_block);
        *previous_to_target_block_size_space = get_available_block_size(previous_to_target_block) + target_block_size;

        *reinterpret_cast<void**>(reinterpret_cast<size_t*>(previous_to_target_block) + 1) = next_available_block_to_target_block;
    }
    else
    {
        auto * const target_block_size_space = reinterpret_cast<size_t*>(target_block);
        *target_block_size_space = target_block_size;

        auto * const first_available_block = get_first_available_block_ptr();
        *first_available_block = target_block;
    }

    this->log_with_guard("[SORTED LIST]Memory at address: " + address + " was deallocated!", fund_alg::logger::severity::trace);
}

sorted_list_memory::~sorted_list_memory()
{
    const auto * const outer_allocator = get_outer_allocator();

    this->log_with_guard("Allocator with sorted list deallocation was deleted!", fund_alg::logger::severity::trace);

    if (outer_allocator == nullptr)
    {
        ::operator delete(_allocated_memory);
    }
    else
    {
        outer_allocator->deallocate(_allocated_memory);
    }
}