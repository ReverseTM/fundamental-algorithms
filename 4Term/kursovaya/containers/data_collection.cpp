#include "data_collection.h"

data_collection::data_collection(): _data(new splay_tree<key, value, key_comparer>()) {}

data_collection::~data_collection()
{
    delete _data;
}