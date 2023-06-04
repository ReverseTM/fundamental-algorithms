#ifndef COMMAND_UPDATE_DATA_H
#define COMMAND_UPDATE_DATA_H

#include <iostream>
#include "command.h"

class command_update_data final : public command
{

private:

    std::string _pool_name;
    std::string _scheme_name;
    std::string _collection_name;

public:

    bool can_execute(std::string const &request) const noexcept final;

    void execute(std::string const &request) const noexcept final;

};

#endif //COMMAND_UPDATE_DATA_H
