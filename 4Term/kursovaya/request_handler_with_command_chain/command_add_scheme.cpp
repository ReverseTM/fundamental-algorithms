#include "command_add_scheme.h"
#include "../containers/data_base.h"

bool command_add_scheme::can_execute(const std::string &request) noexcept
{
    if (request.starts_with("ADD_SCHEME"))
    {
        auto argc = split(request, ' ');

        if (argc.size() == 3)
        {
            _pool_name = argc[1];
            _scheme_name = argc[2];

            return true;
        }
    }

    return false;
}

void command_add_scheme::execute(const std::string &request) const noexcept
{
    data_base::get_instance()->add_scheme(_pool_name, _scheme_name);
}