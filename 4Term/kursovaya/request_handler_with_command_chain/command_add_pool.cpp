#include "command_add_pool.h"

bool command_add_pool::can_execute(const std::string &request) noexcept
{
    if (request.starts_with("ADD_POOL"))
    {
        auto argc = split(request, ' ');

        if (argc.size() == 5)
        {
            _pool_name = argc[1];

            if (argc[2] == "global_heap")
            {
                _pool_allocator_type = allocator_types::GLOBAL_HEAP;
            }
            else if (argc[2] == "sorted_list")
            {
                _pool_allocator_type = allocator_types::SORTED_LIST;
            }
            else if (argc[2] == "border_descriptors")
            {
                _pool_allocator_type = allocator_types::BORDER_DESCRIPTORS;
            }
            else if (argc[2] == "buddies_system")
            {
                _pool_allocator_type = allocator_types::BUDDIES_SYSTEM;
            }
            else
            {
                return false;
            }

            std::stringstream sstream(argc[3]);
            sstream >> _pool_allocator_size;

            if (argc[4] == "first_match")
            {
                _pool_allocator_allocation_mode = memory::allocation_mode::first_match;
            }
            else if (argc[4] == "the_best_match")
            {
                _pool_allocator_allocation_mode = memory::allocation_mode::the_best_match;
            }
            else if (argc[4] == "the_worst_match")
            {
                _pool_allocator_allocation_mode = memory::allocation_mode::the_worst_match;
            }
            else
            {
                return false;
            }

            return true;
        }
    }
    return false;
}

void command_add_pool::execute(const std::string &request) const noexcept
{

}