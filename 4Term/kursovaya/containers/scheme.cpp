#include "scheme.h"

scheme::scheme(): _scheme(new splay_tree<std::string, data_collection*, key_comparer>()) {}

scheme::~scheme()
{
    delete _scheme;
}