#include "command_update_data.h"
#include "../containers/data_base.h"

bool command_update_data::can_execute(const std::string &request) noexcept
{
    if (request.starts_with("UPDATE_DATA"))
    {
        auto argc = split(request, ' ');

        if (argc.size() == 14)
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

            if (_digit_validator(argc[4]))
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
            _surname = argc[8];
            _name = argc[9];
            _patronymic = argc[10];

            if (_date_validator(argc[11]))
            {
                _date = argc[11];
            }
            else
            {
                return false;
            }

            if (_time_validator(argc[12]))
            {
                _time = argc[12];
            }
            else
            {
                return false;
            }

            if (_digit_validator(argc[13]))
            {
                std::stringstream mark(argc[13]);
                mark >> _mark;

                if (_format == form::TEST && (_mark != 1 || _mark != 0 ))
                {
                    return false;
                }
                else
                {
                    if (_mark < 2 || _mark > 5)
                    {
                        return false;
                    }
                }
            }
            else
            {
                return false;
            }

            return true;
        }
    }

    return false;
}

void command_update_data::execute(const std::string &request) const noexcept
{
    data_base::get_instance()->update_data(
            _pool_name,
            _scheme_name,
            _collection_name,
            _id_session,
            _id_student,
            _format,
            _subject,
            _surname,
            _name,
            _patronymic,
            _date,
            _time,
            _mark);
}