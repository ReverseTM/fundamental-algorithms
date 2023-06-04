#include <cmath>
#include <iostream>

#include "data_base.h"

data_base::data_base(): _data_base(new splay_tree<std::string, pool, string_comparer>())
{
    _chain
        .add_handler(new command_add_pool())
        .add_handler(new command_remove_pool())
        .add_handler(new command_add_scheme())
        .add_handler(new command_remove_scheme())
        .add_handler(new command_add_collection())
        .add_handler(new command_remove_collection())
        .add_handler(new command_add_data())
        .add_handler(new command_get_data())
        .add_handler(new command_get_data_between())
        .add_handler(new command_update_data())
        .add_handler(new command_remove_data());
}

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
    const_cast<pool &>(_data_base->find(pool_name)).add(scheme_name, std::move(scheme()));
}

void data_base::add_collection(std::string const & pool_name, std::string const & scheme_name, std::string const & collection_name)
{
    pool const & current_pool = _data_base->find(pool_name);

    memory * allocator = current_pool.get_allocator();

    scheme const & current_scheme = current_pool.find(scheme_name);

    const_cast<scheme &>(current_scheme).add(collection_name, std::move(data_collection(allocator)));
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
    const_cast<data_collection &>(
            _data_base
            ->find(pool_name)
            .find(scheme_name).
            find(collection_name)).add(id_session, id_student, format, subject, surname, name, patronymic, data, time, mark);
}

void data_base::remove_pool(const std::string & pool_name)
{
    _data_base->remove(pool_name);
}

void data_base::remove_scheme(const std::string & pool_name, const std::string & scheme_name)
{
    const_cast<pool &>(_data_base->find(pool_name)).remove(scheme_name);
}

void data_base::remove_collection(const std::string & pool_name, const std::string & scheme_name, const std::string & collection_name)
{
    pool const & current_pool = _data_base->find(pool_name);

    scheme const & current_scheme = current_pool.find(scheme_name);

    const_cast<scheme &>(_data_base->find(pool_name).find(scheme_name)).remove(collection_name);
}

value data_base::remove_data(
        const std::string & pool_name,
        const std::string & scheme_name,
        const std::string & collection_name,
        key * data_key)
{
    return const_cast<data_collection &>(
            _data_base
            ->find(pool_name)
            .find(scheme_name)
            .find(collection_name)).remove(data_key);
}

value * data_base::get_data(
        const std::string & pool_name,
        const std::string & scheme_name,
        const std::string & collection_name,
        key * const & data_key)
{
    return const_cast<data_collection &>(
            _data_base
            ->find(pool_name)
            .find(scheme_name)
            .find(collection_name)).get(data_key);
}

std::vector<value *>data_base::get_data_between_keys(
        const std::string & pool_name,
        const std::string & scheme_name,
        const std::string & collection_name,
        key *const & min_key,
        key *const & max_key)
{
    return const_cast<data_collection &>(
            _data_base
            ->find(pool_name)
            .find(scheme_name)
            .find(collection_name)).get_between_keys(min_key, max_key);
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
    const_cast<data_collection &>(
            _data_base
            ->find(pool_name)
            .find(scheme_name)
            .find(collection_name)).update(id_session, id_student, format, subject, surname, name, patronymic, data, time, mark);
}

void data_base::handle_request(
        std::string const &request)
{
    _chain.handle(request);
}