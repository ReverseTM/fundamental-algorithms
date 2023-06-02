#ifndef DATA_COLLECTION_H
#define DATA_COLLECTION_H

#include "data.h"
#include "../compare/comparator.h"
#include "../tree/splay_tree.h"
#include <string>
#include <tuple>

class data_collection
{

private:

    associative_container<key, value> * _data;

public:

    explicit data_collection();

    ~data_collection();

public:

    data_collection(data_collection const & other) = delete;

    data_collection & operator=(data_collection const & other) = delete;

    data_collection(data_collection && other) = delete;

    data_collection & operator=(data_collection && other) = delete;

};


#endif //DATA_COLLECTION_H
