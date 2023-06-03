#include "key_comparator.h"

int key_comparer::operator()(key * first, key * second)
{
    auto comparison_result = first->_id_session - second->_id_session;
    if (comparison_result != 0)
    {
        return comparison_result;
    }

    comparison_result = first->_id_student - second->_id_student;
    if (comparison_result != 0)
    {
        return comparison_result;
    }

    comparison_result = _string_comparer(first->_format, second->_format);
    if (comparison_result != 0)
    {
        return comparison_result;
    }

    return _string_comparer(first->_subject, second->_subject);
}