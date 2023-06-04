#ifndef COMMAND_ADD_DATA_H
#define COMMAND_ADD_DATA_H

#include "command.h"

class command_add_data final : public command
{

private:

    std::string _pool_name;
    std::string _scheme_name;
    std::string _collection_name;
    unsigned int _id_session;
    unsigned int _id_student;
    form _format;
    std::string _subject;
    std::string _surname;
    std::string _name;
    std::string _patronymic;
    std::string _date;
    std::string _time;
    unsigned int _mark;

public:

    bool can_execute(std::string const &request) noexcept final;

    void execute(std::string const &request) const noexcept final;

};
#endif //COMMAND_ADD_DATA_H
