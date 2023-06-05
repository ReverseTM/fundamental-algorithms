#include "command_get_data_between.h"
#include "../containers/data_base.h"

bool command_get_data_between::can_execute(const std::string &request) noexcept
{
    if (request.starts_with("GET_RANGE"))
    {
        auto argc = split(request, ' ');

        if (argc.size() == 12)
        {
            _pool_name = argc[1];
            _scheme_name = argc[2];
            _collection_name = argc[3];

            if (_digit_validator(argc[4]))
            {
                std::stringstream id_session(argc[4]);
                id_session >> _id_session_for_first_key;
            }
            else
            {
                return false;
            }

            if (_digit_validator(argc[5]))
            {
                std::stringstream id_student(argc[5]);
                id_student >> _id_student_for_first_key;
            }
            else
            {
                return false;
            }

            if (argc[6] == "exam")
            {
                _format_for_first_key = form::EXAM;
            }
            else if (argc[6] == "course_work")
            {
                _format_for_first_key = form::COURSE_WORK;
            }
            else if (argc[6] == "test")
            {
                _format_for_first_key = form::TEST;
            }
            else
            {
                return false;
            }

            _subject_for_first_key = argc[7];

            if (_digit_validator(argc[8]))
            {
                std::stringstream id_session(argc[8]);
                id_session >> _id_session_for_second_key;
            }
            else
            {
                return false;
            }

            if (_digit_validator(argc[9]))
            {
                std::stringstream id_student(argc[9]);
                id_student >> _id_student_for_second_key;
            }
            else
            {
                return false;
            }

            if (argc[10] == "exam")
            {
                _format_for_second_key = form::EXAM;
            }
            else if (argc[10] == "course_work")
            {
                _format_for_second_key = form::COURSE_WORK;
            }
            else if (argc[10] == "test")
            {
                _format_for_second_key = form::TEST;
            }
            else
            {
                return false;
            }

            _subject_for_second_key = argc[11];

            return true;
        }
    }

    return false;
}

void command_get_data_between::execute(const std::string &request) const noexcept
{
    key * first_key = new key();

    first_key->_id_session = _id_session_for_first_key;
    first_key->_id_student = _id_student_for_first_key;
    first_key->_format = _format_for_first_key;
    first_key->_subject = _subject_for_first_key;

    key * second_key = new key();

    second_key->_id_session = _id_session_for_second_key;
    second_key->_id_student = _id_student_for_second_key;
    second_key->_format = _format_for_second_key;
    second_key->_subject = _subject_for_second_key;

    data_base::get_instance()->get_data_between_keys(
            _pool_name,
            _scheme_name,
            _collection_name,
            first_key,
            second_key);

    delete first_key;
    delete second_key;
}