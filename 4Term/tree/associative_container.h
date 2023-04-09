#ifndef ASSOCIATIVE_CONTAINER_H
#define ASSOCIATIVE_CONTAINER_H

template<
    typename tkey,
    typename tvalue>
class associative_container
{

public:

    virtual void insert(tkey const &key, tvalue const &&value) = 0;

    virtual tvalue const &get(tkey const &key) = 0;

    virtual tvalue &&remove(tkey const &key) = 0;


public:

    virtual ~associative_container() = default;

};

#endif //ASSOCIATIVE_CONTAINER_H
