#ifndef ASSOCIATIVE_CONTAINER_H
#define ASSOCIATIVE_CONTAINER_H

template<typename tkey, typename tvalue>
class associative_container
{

public:

    struct key_value_pair
    {
        tkey _key;
        tvalue _value;
    };

public:

    virtual void insert(tkey const &key, tvalue const &&value) = 0;

    virtual bool find(key_value_pair * target_key_and_result_value) = 0;

    virtual tvalue &&remove(tkey const &key) = 0;


public:

    virtual ~associative_container() = default;

};

#endif //ASSOCIATIVE_CONTAINER_H
