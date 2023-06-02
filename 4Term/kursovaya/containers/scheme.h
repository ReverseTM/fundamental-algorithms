#ifndef SCHEME_H
#define SCHEME_H

#include "data_collection.h"
#include "data_base.h"

class scheme
{
    friend class data_base;

private:

    associative_container<std::string, data_collection*> * _scheme;

public:

    explicit scheme();

    ~scheme();

public:

    scheme(scheme const & other) = delete;

    scheme & operator=(scheme const & other) = delete;

    scheme(scheme && other) = delete;

    scheme & operator=(scheme && other) = delete;

};


#endif //SCHEME_H
