#include "command_add_collection.h"

bool command_add_collection::can_execute(const std::string &request) noexcept
{
    if (request.starts_with("ADD_COLLECTION"))
    {
        auto argc = split(request, ' ');

        if (argc.size() == 4)
        {
            _pool_name = argc[1];
            _scheme_name = argc[2];
            _collection_name = argc[3];

            return true;
        }
    }

    return false;
}

void command_add_collection::execute(const std::string &request) const noexcept
{

}