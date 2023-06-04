#ifndef COMMAND_ADD_POOL_H
#define COMMAND_ADD_POOL_H

#include "command.h"
#include "../types/allocator_types.h"

class command_add_pool final : public command
{

private:

    std::string _pool_name;
    allocator_types _pool_allocator_type;
    unsigned int _pool_allocator_size;
    memory::allocation_mode _pool_allocator_allocation_mode;

public:

    bool can_execute(std::string const &request) const noexcept final;

    void execute(std::string const &request) const noexcept final;

};
#endif //COMMAND_ADD_POOL_H
