#ifndef STRING_COMPARER_H
#define STRING_COMPARER_H

#include "../types/data_type.h"

class string_comparer final
{

public:

    int operator()(std::string const & first, std::string const & second);
};


#endif //STRING_COMPARER_H
