#include "border_descriptors_allocator.h"

size_t border_descriptors_allocator::get_allocator_service_block_size() const
{
    return sizeof(size_t) + sizeof(memory*) + sizeof(fund_alg::logger*) + sizeof(memory::allocation_mode) + sizeof(void*);
}

size_t border_descriptors_allocator::get_allocated_memory_size() const
{
    return *reinterpret_cast<size_t*>(_allocated_memory);
}

memory* border_descriptors_allocator::get_outer_allocator() const
{
    return *reinterpret_cast<memory**>(reinterpret_cast<unsigned char*>(_allocated_memory) + sizeof(size_t));
}

fund_alg::logger const * const border_descriptors_allocator::get_logger() const
{
    return *reinterpret_cast<fund_alg::logger**>(reinterpret_cast<unsigned char*>(_allocated_memory) + sizeof(size_t) + sizeof(memory*));
}

memory::allocation_mode border_descriptors_allocator::get_allocation_mode() const
{
    return *reinterpret_cast<memory::allocation_mode*>(reinterpret_cast<unsigned char*>(_allocated_memory) + sizeof(size_t) + sizeof(memory*) + sizeof(fund_alg::logger*));
}

void* border_descriptors_allocator::get_first_occupied_block() const
{
    return *reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(_allocated_memory) + sizeof(size_t) + sizeof(memory*) + sizeof(fund_alg::logger*) + sizeof(allocation_mode));
}

void** border_descriptors_allocator::get_first_occupied_block_ptr() const
{
    return reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(_allocated_memory) + sizeof(size_t) + sizeof(memory*) + sizeof(fund_alg::logger*) + sizeof(allocation_mode));
}

void * border_descriptors_allocator::get_next_occupied_block(void * current_block) const
{
    return *reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(current_block) + sizeof(size_t) + sizeof(void*));
}

void * border_descriptors_allocator::get_previous_occupied_block(void *current_block) const
{
    return *reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(current_block) + sizeof(size_t));
}

size_t border_descriptors_allocator::get_available_block_size(void * first_occupied_block_to_target_block) const
{
    auto previous_block = get_previous_occupied_block(first_occupied_block_to_target_block);
    auto start_allocated_memory = get_start_allocated_memory_address();
    size_t difference_between_current_and_start = (reinterpret_cast<unsigned char*>(first_occupied_block_to_target_block) - reinterpret_cast<unsigned char*>(start_allocated_memory));

    if (previous_block != nullptr)
    {
        return *reinterpret_cast<size_t*>(reinterpret_cast<unsigned char*>(first_occupied_block_to_target_block) - (reinterpret_cast<unsigned char*>(previous_block) + get_occupied_block_size(previous_block)));
    }
    else if (reinterpret_cast<void*>(reinterpret_cast<unsigned char*>(first_occupied_block_to_target_block) - difference_between_current_and_start) == start_allocated_memory)
    {
        return difference_between_current_and_start;
    }
    else
    {
        return 0;
    }
}

size_t border_descriptors_allocator::get_occupied_block_service_block_size() const
{
    return sizeof(size_t) + sizeof(void *) + sizeof(void *);
}

size_t border_descriptors_allocator::get_occupied_block_size(void * current_block) const
{
    return *reinterpret_cast<size_t*>(current_block);
}

size_t border_descriptors_allocator::get_occupied_block_size_without_service_block(void * current_block) const
{
    return get_occupied_block_size(current_block) - get_occupied_block_service_block_size();
}

void * border_descriptors_allocator::get_start_allocated_memory_address() const
{
    return reinterpret_cast<void*>(reinterpret_cast<unsigned char*>(_allocated_memory) + get_allocator_service_block_size());
}

void * border_descriptors_allocator::get_end_allocated_memory_address() const
{
    return reinterpret_cast<void*>(reinterpret_cast<unsigned char*>(_allocated_memory) + get_allocated_memory_size());
}

void * border_descriptors_allocator::get_address_relative_to_allocator(void * current_block_address) const
{
    return reinterpret_cast<void*>(reinterpret_cast<unsigned char*>(current_block_address) - reinterpret_cast<unsigned char*>(get_start_allocated_memory_address()));
}

border_descriptors_allocator::border_descriptors_allocator(
        size_t target_size,
        memory::allocation_mode mode,
        fund_alg::logger *logger,
        memory *outer_allocator)
{
    size_t occupied_block_service_block_size = get_occupied_block_service_block_size();

    size_t allocator_service_block_size = get_allocator_service_block_size();

    size_t memory_size = allocator_service_block_size + occupied_block_service_block_size + target_size;

    if (outer_allocator == nullptr)
    {
        _allocated_memory = ::operator new(memory_size);
    }
    else
    {
        _allocated_memory = outer_allocator->allocate(memory_size);
    }

    auto * const allocated_memory_size = reinterpret_cast<size_t*>(_allocated_memory);
    *allocated_memory_size = memory_size;

    auto * const outer_allocator_ptr = reinterpret_cast<memory**>(allocated_memory_size + 1);
    *outer_allocator_ptr = outer_allocator;

    auto * const logger_ptr = reinterpret_cast<fund_alg::logger**>(outer_allocator_ptr + 1);
    *logger_ptr = logger;

    auto * const allocation_mode_ptr = reinterpret_cast<memory::allocation_mode*>(logger_ptr + 1);
    *allocation_mode_ptr = mode;

    auto * const first_occupied_block_ptr = reinterpret_cast<void**>(allocation_mode_ptr + 1);
    *first_occupied_block_ptr = nullptr;

    this->trace_with_guard("[BORDER DESCRIPTORS ALLOCATOR] Allocator successfully created.");
}

void * const border_descriptors_allocator::allocate(size_t request_size) const
{
    size_t occupied_block_service_block_size = get_occupied_block_service_block_size();
    size_t target_block_size = 0;
    void * previous_block = nullptr;
    auto current_block = get_first_occupied_block();
    void * previous_occupied_block = nullptr;
    void * target_block = nullptr;
    void * next_occupied_block = nullptr;
    auto allocation_mode = get_allocation_mode();

    if (current_block == nullptr)
    {
        auto current_available_block_size = get_allocated_memory_size() - get_allocator_service_block_size();

        if (current_available_block_size >= request_size + occupied_block_service_block_size)
        {
            target_block = get_start_allocated_memory_address();
        }
    }
    else {

        while (current_block != nullptr) {

            auto next_block = get_next_occupied_block(current_block);
            auto current_available_block_size = get_available_block_size(current_block);

            if (current_available_block_size >= request_size + occupied_block_service_block_size) {
                if (
                        allocation_mode == memory::allocation_mode::first_match ||
                        allocation_mode == memory::allocation_mode::the_best_match && (target_block == nullptr || current_available_block_size < target_block_size) || allocation_mode == memory::allocation_mode::the_worst_match && (target_block == nullptr || current_available_block_size > target_block_size)
                        )
                {
                    target_block_size = current_available_block_size;
                    previous_occupied_block = previous_block;
                    target_block = reinterpret_cast<void*>(reinterpret_cast<unsigned char*>(current_block) - current_available_block_size);
                    next_occupied_block = current_block;
                }

                if (allocation_mode == memory::allocation_mode::first_match)
                {
                    break;
                }
            }

            previous_block = current_block;
            current_block = next_block;
        }

        previous_occupied_block = previous_block;
        void * end_allocated_memory = get_end_allocated_memory_address();

        if (target_block == nullptr)
        {
            size_t current_available_block_size = (reinterpret_cast<unsigned char*>(end_allocated_memory) - (reinterpret_cast<unsigned char*>(previous_block) + get_occupied_block_size(previous_block)));

            if (current_available_block_size >= request_size + occupied_block_service_block_size)
            {
                target_block = reinterpret_cast<void *>(reinterpret_cast<unsigned char *>(previous_block) + get_occupied_block_size(previous_block));
            }
        }
    }

    if (target_block == nullptr)
    {
        std::string message = "No available memory";
        this->warning_with_guard("[BORDER DESCRIPTORS ALLOCATOR] " + message + ".");

        throw memory::memory_exception(message);
    }

    auto target_block_size_space = reinterpret_cast<size_t*>(target_block);
    *target_block_size_space = request_size + occupied_block_service_block_size;

    std::cout << "size = " << *target_block_size_space << std::endl;

    auto * const previous_block_to_target_block = reinterpret_cast<void**>(target_block_size_space + 1);
    *previous_block_to_target_block = previous_occupied_block;

    std::cout << "prev block address: " << *previous_block_to_target_block << std::endl;

    auto * const next_block_to_target_block = reinterpret_cast<void**>(previous_block_to_target_block + 1);
    *next_block_to_target_block = next_occupied_block;

    std::cout << "next block address: " << *next_block_to_target_block << std::endl;

    if (previous_occupied_block != nullptr)
    {
        auto * const next_block_to_previous_block = reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(previous_occupied_block) + sizeof(size_t) + sizeof(void*));
        *next_block_to_previous_block = target_block;
    }
    else
    {
        auto * const first_occupied_block = get_first_occupied_block_ptr();
        *first_occupied_block = target_block;
    }

    std::cout << "current block address: " << target_block << std::endl;

    return reinterpret_cast<void*>(next_block_to_target_block + 1);
}

void border_descriptors_allocator::deallocate(void *target_to_dealloc) const
{

}

border_descriptors_allocator::~border_descriptors_allocator()
{
    const auto * const outer_allocator = get_outer_allocator();

    this->trace_with_guard("[BORDER DESCRIPTORS ALLOCATOR] Allocator success deleted.");

    if (outer_allocator == nullptr)
    {
        ::operator delete(_allocated_memory);
    }
    else
    {
        outer_allocator->deallocate(_allocated_memory);
    }
}