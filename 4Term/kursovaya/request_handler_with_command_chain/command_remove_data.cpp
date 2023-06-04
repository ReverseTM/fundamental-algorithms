#include "command_remove_data.h"

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

            return true;
        }
    }

    return false;
}

void command_remove_data::execute(const std::string &request) const noexcept
{

}