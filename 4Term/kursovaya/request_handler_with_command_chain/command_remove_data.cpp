#include "command_remove_data.h"
#include "../containers/data_base.h"

bool command_remove_data::can_execute(const std::string &request) noexcept
{
    if (request.starts_with("REMOVE_DATA"))
    {
        auto argc = split(request, ' ');

        if (argc.size() == 8)
        {
            _pool_name = argc[1];
            _scheme_name = argc[2];
            _collection_name = argc[3];

            if (_digit_validator(argc[4]))
            {
                std::stringstream id_session(argc[4]);
                id_session >> _id_session;
            }
            else
            {
                return false;
            }

            if (_digit_validator(argc[5]))
            {
                std::stringstream id_student(argc[5]);
                id_student >> _id_student;
            }
            else
            {
                return false;
            }

            if (argc[6] == "exam")
            {
                _format = form::EXAM;
            }
            else if (argc[6] == "course_work")
            {
                _format = form::COURSE_WORK;
            }
            else if (argc[6] == "test")
            {
                _format = form::TEST;
            }
            else
            {
                return false;
            }

            _subject = argc[7];

            return true;
        }
    }

    return false;
}

void command_remove_data::execute(const std::string &request) const noexcept
{
    key * data_key = new key();

    data_key->_id_session = _id_session;
    data_key->_id_student = _id_student;
    data_key->_format = _format;
    data_key->_subject = _subject;

    data_base::get_instance()->remove_data(_pool_name, _scheme_name, _collection_name, data_key);

    delete data_key;
}