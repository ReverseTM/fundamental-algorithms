#ifndef SCHEME_H
#define SCHEME_H

#include "data_collection.h"

class scheme final
{
    friend class data_base;

private:

    associative_container<std::string, data_collection> * _scheme;

public:

    scheme();

    ~scheme();

public:

    void add(std::string const &key, data_collection && target);

    void remove(std::string const & key);

    bool find(associative_container<std::string, data_collection>::key_value_pair * target_key_and_value);

public:

    scheme(scheme const & other);

    scheme & operator=(scheme const & other);

    scheme(scheme && other) noexcept;

    scheme & operator=(scheme && other) noexcept;

};


#endif //SCHEME_H
