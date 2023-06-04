#include <iostream>
#include "data_base.h"
#include <cmath>


data_base::data_base(): _data_base(new splay_tree<std::string, pool, string_comparer>()) {}

data_base::~data_base()
{
    delete _data_base;
}

void data_base::add_pool(std::string const & pool_name, allocator_types allocator_name, size_t request_size, memory::allocation_mode mode)
{
    memory * allocator = nullptr;

    switch (allocator_name)
    {
        case allocator_types::GLOBAL_HEAP:
            allocator = new global_heap_allocator();
            break;

        case allocator_types::SORTED_LIST:
            allocator = new sorted_list_allocator(request_size, mode);
            break;

        case allocator_types::BORDER_DESCRIPTORS:
            allocator = new border_descriptors_allocator(request_size, mode);
            break;

        case allocator_types::BUDDIES_SYSTEM:
            request_size = static_cast<size_t>(log2(request_size)) + 1;
            allocator = new buddy_system_allocator(request_size, mode);
            break;
    }

    _data_base->insert(pool_name, std::move(pool(allocator)));
}

void data_base::add_scheme(std::string const & pool_name, std::string const & scheme_name)
{
    associative_container<std::string, pool>::key_value_pair pair {pool_name};

    if (!_data_base->find(&pair))
    {
        throw std::exception();
    }

    pair._value.add(scheme_name, std::move(scheme()));
}

void data_base::add_collection(std::string const & pool_name, std::string const & scheme_name, std::string const & collection_name)
{
    associative_container<std::string, pool>::key_value_pair pair_pool {pool_name};

    if (!_data_base->find(&pair_pool))
    {
        throw std::exception();
    }

    memory * allocator = pair_pool._value.get_allocator();

    associative_container<std::string, scheme>::key_value_pair pair_scheme {scheme_name};

    if (!pair_pool._value.find(&pair_scheme))
    {
        throw std::exception();
    }

    pair_scheme._value.add(collection_name, std::move(data_collection(allocator)));
}

void data_base::add_data(
        const std::string & pool_name,
        const std::string & scheme_name,
        const std::string & collection_name,
        unsigned int id_session,
        unsigned int id_student,
        form format,
        const std::string & subject,
        const std::string & surname,
        const std::string & name,
        const std::string & patronymic,
        const std::string & data,
        const std::string & time,
        unsigned int mark)
{
    associative_container<std::string, pool>::key_value_pair pair_pool {pool_name};

    if (!_data_base->find(&pair_pool))
    {
        throw std::exception();
    }

    associative_container<std::string, scheme>::key_value_pair pair_scheme {scheme_name};

    if (!pair_pool._value.find(&pair_scheme))
    {
        throw std::exception();
    }

    associative_container<std::string, data_collection>::key_value_pair collection_pair {collection_name};

    if (!pair_scheme._value.find(&collection_pair))
    {
        throw std::exception();
    }

    collection_pair._value.add(id_session, id_student, format, subject, surname, name, patronymic, data, time, mark);
}

void data_base::remove_pool(const std::string & name)
{
    _data_base->remove(name);
}

void data_base::remove_scheme(const std::string & pool_name, const std::string & scheme_name)
{
    associative_container<std::string, pool>::key_value_pair pair {pool_name};

    if (!_data_base->find(&pair))
    {
        throw std::exception();
    }

    pair._value.remove(scheme_name);
}

void data_base::remove_collection(const std::string & pool_name, const std::string & scheme_name, const std::string & collection_name)
{
    associative_container<std::string, pool>::key_value_pair pool_pair {pool_name};

    if (!_data_base->find(&pool_pair))
    {
        throw std::exception();
    }

    associative_container<std::string, scheme>::key_value_pair scheme_pair {scheme_name};

    if (!pool_pair._value.find(& scheme_pair))
    {
        throw std::exception();
    }

    scheme_pair._value.remove(collection_name);
}

value data_base::remove_data(
        const std::string & pool_name,
        const std::string & scheme_name,
        const std::string & collection_name,
        key * data_key)
{
    associative_container<std::string, pool>::key_value_pair pool_pair {pool_name};

    if (!_data_base->find(&pool_pair))
    {
        throw std::exception();
    }

    associative_container<std::string, scheme>::key_value_pair scheme_pair {scheme_name};

    if (!pool_pair._value.find(&scheme_pair))
    {
        throw std::exception();
    }

    associative_container<std::string, data_collection>::key_value_pair collection_pair {collection_name};

    if (!scheme_pair._value.find(&collection_pair))
    {
        throw std::exception();
    }

    return collection_pair._value.remove(data_key);
}

value * data_base::get_data(
        const std::string & pool_name,
        const std::string & scheme_name,
        const std::string & collection_name,
        key * const & data_key)
{
    associative_container<std::string, pool>::key_value_pair pool_pair {pool_name};

    if (!_data_base->find(&pool_pair))
    {
        throw std::exception();
    }

    associative_container<std::string, scheme>::key_value_pair scheme_pair {scheme_name};

    if (!pool_pair._value.find(&scheme_pair))
    {
        throw std::exception();
    }

    associative_container<std::string, data_collection>::key_value_pair collection_pair {collection_name};

    if (!scheme_pair._value.find(&collection_pair))
    {
        throw std::exception();
    }

    return collection_pair._value.get(data_key);
}

std::vector<value *>data_base::get_data_between_keys(
        const std::string & pool_name,
        const std::string & scheme_name,
        const std::string & collection_name,
        key *const & min_key,
        key *const & max_key)
{
    associative_container<std::string, pool>::key_value_pair pool_pair {pool_name};

    if (!_data_base->find(&pool_pair))
    {
        throw std::exception();
    }

    associative_container<std::string, scheme>::key_value_pair scheme_pair {scheme_name};

    if (!pool_pair._value.find(&scheme_pair))
    {
        throw std::exception();
    }

    associative_container<std::string, data_collection>::key_value_pair collection_pair {collection_name};

    if (!scheme_pair._value.find(&collection_pair))
    {
        throw std::exception();
    }

    return collection_pair._value.get_between_keys(min_key, max_key);
}

void data_base::update_data(
        const std::string & pool_name,
        const std::string & scheme_name,
        const std::string & collection_name,
        unsigned int id_session,
        unsigned int id_student,
        form format,
        const std::string & subject,
        const std::string & surname,
        const std::string & name,
        const std::string & patronymic,
        const std::string & data,
        const std::string & time,
        unsigned int mark)
{
    associative_container<std::string, pool>::key_value_pair pair_pool {pool_name};

    if (!_data_base->find(&pair_pool))
    {
        throw std::exception();
    }

    associative_container<std::string, scheme>::key_value_pair pair_scheme {scheme_name};

    if (!pair_pool._value.find(&pair_scheme))
    {
        throw std::exception();
    }

    associative_container<std::string, data_collection>::key_value_pair collection_pair {collection_name};

    if (!pair_scheme._value.find(&collection_pair))
    {
        throw std::exception();
    }

    collection_pair._value.update(id_session, id_student, format, subject, surname, name, patronymic, data, time, mark);
}