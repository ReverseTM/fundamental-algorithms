#include "comparator.h"

int key_comparer::operator()(std::string first, std::string second)
{
    if (first > second)
        return 1;
    else if (first < second)
        return -1;
    else
        return 0;
}

int key_comparer::operator()(key first, key second)
{
    if (first._id_session < second._id_session)
    {
        return -1;
    }
    else
    {
        return 1;
    }

    if (first._id_student < second._id_student)
    {
        return -1;
    }
    else
    {
        return 1;
    }

    if (first._format < second._format)
    {
        return -1;
    }
    else
    {
        return 1;
    }

    if (first._subject < second._format)
    {
        return -1;
    }
    else
    {
        return 1;
    }

    return 0;
}