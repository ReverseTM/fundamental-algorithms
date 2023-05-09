#ifndef ASSOCIATIVE_CONTAINER_H
#define ASSOCIATIVE_CONTAINER_H

template<typename tkey, typename tvalue>
class associative_container
{

public:

    struct key_value_pair final
    {
        tkey _key;
        tvalue _value;

        key_value_pair(): _key(0), _value(0) {};
        key_value_pair(int key): _key(key), _value(0) {};
        key_value_pair(int key, int value): _key(key), _value(value) {};
    };

public:

    virtual void insert(tkey const &key, tvalue &&value) = 0;

    virtual bool find(key_value_pair * target_key_and_result_value) = 0;

    virtual tvalue && remove(tkey const &key) = 0;

public:

    void operator+=(key_value_pair pair);

    bool operator[](key_value_pair * target_key_and_result_value);

    tvalue && operator-=(tkey const &key);

public:

    virtual ~associative_container() = default;

};

template<
    typename tkey,
    typename tvalue>
void associative_container<tkey, tvalue>::operator+=(key_value_pair pair)
{
    insert(pair._key, std::move(pair._value));
}

template<
    typename tkey,
    typename tvalue>
bool associative_container<tkey, tvalue>::operator[](key_value_pair *target_key_and_result_value)
{
    return find(target_key_and_result_value);
}

template<
    typename tkey,
    typename tvalue>
tvalue && associative_container<tkey,tvalue>::operator-=(const tkey &key)
{
    return std::move(remove(key));
}

#endif //ASSOCIATIVE_CONTAINER_H
