#ifndef KEY_COMPARER_H
#define KEY_COMPARER_H

#include "../types/data_type.h"
#include "string_comparer.h"

class key_comparer final
{

private:

    string_comparer _string_comparer;

public:

    int operator()(key * first, key * second);

};


#endif //KEY_COMPARER_H
