#ifndef HANDLER_H
#define HANDLER_H


template<typename trequest>
class handler
{

    friend class request_handler_with_command_chain<trequest>;

protected:

    handler<trequest> *  _next_handler;

public:

    handler() : _next_handler(nullptr)
    {

    }

    virtual ~handler() = default;

public:

    virtual bool handle(trequest const &) const noexcept = 0;

};


#endif //HANDLER_H
