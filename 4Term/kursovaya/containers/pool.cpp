#include "pool.h"

pool::pool(): _pool(new splay_tree<std::string, scheme*, key_comparer>()) {}

pool::~pool()
{
    delete _pool;
}
