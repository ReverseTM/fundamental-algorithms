#ifndef COMMAND_GET_DATA_BETWEEN_H
#define COMMAND_GET_DATA_BETWEEN_H

#include "command.h"

class command_get_data_between final : public command
{

private:

    digit_validator _digit_validator;

    std::string _pool_name;
    std::string _scheme_name;
    std::string _collection_name;
    unsigned int _id_session_for_first_key;
    unsigned int _id_student_for_first_key;
    form _format_for_first_key;
    std::string _subject_for_first_key;
    unsigned int _id_session_for_second_key;
    unsigned int _id_student_for_second_key;
    form _format_for_second_key;
    std::string _subject_for_second_key;

public:

    bool can_execute(std::string const &request) noexcept final;

    void execute(std::string const &request) const noexcept final;

};
#endif //COMMAND_GET_DATA_BETWEEN_H
