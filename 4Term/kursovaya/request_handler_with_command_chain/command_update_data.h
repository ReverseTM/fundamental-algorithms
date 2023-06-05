#ifndef COMMAND_UPDATE_DATA_H
#define COMMAND_UPDATE_DATA_H

#include <iostream>
#include "command.h"

class command_update_data final : public command
{

private:

    digit_validator _digit_validator;
    date_validator _date_validator;
    time_validator _time_validator;

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

#endif //COMMAND_UPDATE_DATA_H
