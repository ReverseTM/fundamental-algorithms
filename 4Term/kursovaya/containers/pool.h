#ifndef POOL_H
#define POOL_H

#include "scheme.h"
#include "data_base.h"

class pool
{

    friend class data_base;

private:

    memory * _allocator;

    associative_container<std::string, scheme *> * _pool;

public:

    explicit pool();

    ~pool();

public:

    pool(pool const & other) = delete;

    pool & operator=(pool const & other) = delete;

    pool(pool && other) = delete;

    explicit pool(associative_container<std::string, scheme *> *pool);

    pool & operator=(pool && other) = delete;

};


#endif //POOL_H
