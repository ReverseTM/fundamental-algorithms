#ifndef HANDLER_IMPLEMENTATION_H
#define HANDLER_IMPLEMENTATION_H

#include "handler.h"

template<typename trequest> class request_handler_with_command : public handler<trequest>
{

private:

    command<trequest> * _target_action;

public:
    request_handler_with_command(command<trequest> * target_action) : _target_action(target_action) {}

    ~request_handler_with_command()
    {
        delete _target_action;
    }

    request_handler_with_command(request_handler_with_command const &) = delete;
    request_handler_with_command(request_handler_with_command &&) = delete;
    request_handler_with_command &operator=(request_handler_with_command const &) = delete;
    request_handler_with_command &operator=(request_handler_with_command &&) = delete;

public:

    bool handle(trequest const &request) const noexcept final
    {
        if (!_target_action->can_execute(request))
        {
            if (abstract_handler<trequest>::_next_handler == nullptr)
            {
                return false;
            }

            return abstract_handler<trequest>::_next_handler->handle(request);
        }

        _target_action->execute(request);
        return true;
    }
};


#endif //HANDLER_IMPLEMENTATION_H
