#include "string_comparer.h"

int string_comparer::operator()(std::string const & first, std::string const & second)
{
    if (first > second)
        return 1;
    else if (first < second)
        return -1;
    else
        return 0;
}
