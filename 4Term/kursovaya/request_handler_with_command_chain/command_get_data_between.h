#ifndef COMMAND_GET_DATA_BETWEEN_H
#define COMMAND_GET_DATA_BETWEEN_H

#include "command.h"

class command_get_data_between final : public command
{

private:

    std::string _pool_name;
    std::string _scheme_name;
    std::string _collection_name;

public:

    bool can_execute(std::string const &request) const noexcept final;

    void execute(std::string const &request) const noexcept final;

};
#endif //COMMAND_GET_DATA_BETWEEN_H
