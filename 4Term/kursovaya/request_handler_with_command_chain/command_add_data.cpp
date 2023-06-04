#include "command_add_data.h"

bool command_add_data::can_execute(const std::string &request) noexcept
{
    if (request.starts_with("ADD_DATA"))
    {
        auto argc = split(request, ' ');

        if (argc.size() == 14)
        {
            _pool_name = argc[1];
            _scheme_name = argc[2];
            _collection_name = argc[3];

            std::stringstream id_session(argc[4]);
            id_session >> _id_session;

            std::stringstream id_student(argc[5]);
            id_student >> _id_student;

            if (argc[6] == "EXAM")
            {
                _format = form::EXAM;
            }
            else if (argc[6] == "COURSE_WORK")
            {
                _format = form::COURSE_WORK;
            }
            else if (argc[6] == "TEST")
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
            _date = argc[11];
            _time = argc[12];

            std::stringstream mark(argc[13]);
            mark >> _mark;

            return true;
        }
    }

    return false;
}

void command_add_data::execute(const std::string &request) const noexcept
{

}