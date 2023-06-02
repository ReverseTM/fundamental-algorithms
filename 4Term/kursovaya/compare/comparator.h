#ifndef COMPARATOR_H
#define COMPARATOR_H
#include <iostream>
#include "../containers/data.h"

class key_comparer
{
public:

    int operator()(std::string first, std::string second);

    int operator()(key first, key second);
};


#endif //COMPARATOR_H
