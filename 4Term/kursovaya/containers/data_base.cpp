#include <cmath>
#include <iostream>

#include "data_base.h"
#include "../request_handler_with_command_chain/request_handler_with_command_chain.h"
#include "../request_handler_with_command_chain/command_add_pool.h"
#include "../request_handler_with_command_chain/command_remove_pool.h"
#include "../request_handler_with_command_chain/command_add_scheme.h"
#include "../request_handler_with_command_chain/command_remove_scheme.h"
#include "../request_handler_with_command_chain/command_add_collection.h"
#include "../request_handler_with_command_chain/command_remove_collection.h"
#include "../request_handler_with_command_chain/command_add_data.h"
#include "../request_handler_with_command_chain/command_get_data.h"
#include "../request_handler_with_command_chain/command_get_data_between.h"
#include "../request_handler_with_command_chain/command_update_data.h"
#include "../request_handler_with_command_chain/command_remove_data.h"

data_base *data_base::_instance = nullptr;

data_base::data_base()
{
    _data_base = new splay_tree<std::string, pool, string_comparer>();

    _chain
        .add_handler(new command_add_pool())
        .add_handler(new command_remove_pool())
        .add_handler(new command_add_scheme())
        .add_handler(new command_remove_scheme())
        .add_handler(new command_add_collection())
        .add_handler(new command_remove_collection())
        .add_handler(new command_add_data())
        .add_handler(new command_remove_data())
        .add_handler(new command_get_data())
        .add_handler(new command_get_data_between())
        .add_handler(new command_update_data());

    _instance = this;
}

data_base::~data_base()
{
    delete _data_base;
}

void data_base::add_pool(std::string const & pool_name, allocator_types allocator_name, size_t request_size, memory::allocation_mode mode)
{
    try
    {
        memory *allocator = nullptr;

        switch (allocator_name) {
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

        std::cout << "[DATA BASE] pool added to data base" << std::endl << std::endl;
    }
    catch (std::exception const &ex)
    {
        std::cout << ex.what() << std::endl;
    }
}

void data_base::add_scheme(std::string const & pool_name, std::string const & scheme_name)
{
    try
    {
        const_cast<pool &>(_data_base->find(pool_name)).add(scheme_name, std::move(scheme()));

        std::cout << "[DATA BASE] scheme added to " << pool_name << std::endl << std::endl;
    }
    catch (std::exception const &ex)
    {
        std::cout << ex.what() << std::endl;
    }
}

void data_base::add_collection(std::string const & pool_name, std::string const & scheme_name, std::string const & collection_name)
{
    try
    {
        pool const &current_pool = _data_base->find(pool_name);

        memory *allocator = current_pool.get_allocator();

        scheme const &current_scheme = current_pool.find(scheme_name);

        const_cast<scheme &>(current_scheme).add(collection_name, std::move(data_collection(allocator)));

        std::cout << "[DATA BASE] collection added to " << pool_name << " " << scheme_name << std::endl << std::endl;
    }
    catch (std::exception const &ex)
    {
        std::cout << ex.what() << std::endl;
    }
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
    try
    {
        const_cast<data_collection &>(
                _data_base
                ->find(pool_name)
                .find(scheme_name)
                .find(collection_name)).add(id_session, id_student, format, subject, surname, name, patronymic, data, time, mark);

        std::cout << "[DATA BASE] data added to " << pool_name << " " << scheme_name << " " << collection_name << std::endl << std::endl;
    }
    catch (std::exception const &ex)
    {
        std::cout << ex.what() << std::endl;
    }
}

void data_base::remove_pool(const std::string & pool_name)
{
    try
    {
        _data_base->remove(pool_name);

        std::cout << "[DATA BASE] pool removed from data base" << std::endl << std::endl;
    }
    catch (std::exception const &ex)
    {
        std::cout << ex.what() << std::endl;
    }
}

void data_base::remove_scheme(const std::string & pool_name, const std::string & scheme_name)
{
    try
    {
        const_cast<pool &>(_data_base->find(pool_name)).remove(scheme_name);

        std::cout << "[DATA BASE] scheme removed from " << pool_name << std::endl << std::endl;
    }
    catch (std::exception const &ex)
    {
        std::cout << ex.what() << std::endl;
    }
}

void data_base::remove_collection(const std::string & pool_name, const std::string & scheme_name, const std::string & collection_name)
{
    try
    {
        const_cast<scheme &>(_data_base->find(pool_name).find(scheme_name)).remove(collection_name);

        std::cout << "[DATA BASE] collection removed from " << pool_name << " " << scheme_name << std::endl << std::endl;
    }
    catch (std::exception const &ex)
    {
        std::cout << ex.what() << std::endl;
    }
}

value data_base::remove_data(
        const std::string & pool_name,
        const std::string & scheme_name,
        const std::string & collection_name,
        key * data_key)
{
    try
    {
        value data = const_cast<data_collection &>(
                _data_base
                ->find(pool_name)
                .find(scheme_name)
                .find(collection_name)).remove(data_key);

        std::cout << "[DATA BASE] data removed from " << pool_name << " " << scheme_name << " " << collection_name << std::endl << std::endl;

        return data;
    }
    catch (std::exception const &ex)
    {
        std::cout << ex.what() << std::endl;
    }
}

value * data_base::get_data(
        const std::string & pool_name,
        const std::string & scheme_name,
        const std::string & collection_name,
        key * const & data_key)
{
    try
    {
        value * data = const_cast<data_collection &>(
                _data_base
                ->find(pool_name)
                .find(scheme_name)
                .find(collection_name)).get(data_key);

        std::cout << "[DATA BASE] received value from " << pool_name << " " << scheme_name << " " << collection_name << std::endl << std::endl;

        std::cout << "\tData" << std::endl;

        std::cout << "surname: " << data->_surname << std::endl;
        std::cout << "name: " << data->_name << std::endl;
        std::cout << "patronymic: " << data->_patronymic << std::endl;
        std::cout << "date: " << data->_date << std::endl;
        std::cout << "time: " << data->_time << std::endl;
        std::cout << "mark: " << data->_mark << std::endl;

        return data;
    }
    catch (std::exception const &ex)
    {
        std::cout << ex.what() << std::endl;
    }
}

std::vector<value *>data_base::get_data_between_keys(
        const std::string & pool_name,
        const std::string & scheme_name,
        const std::string & collection_name,
        key *const & min_key,
        key *const & max_key)
{
    try
    {
        std::vector<value *> data = const_cast<data_collection &>(
                _data_base
                ->find(pool_name)
                .find(scheme_name)
                .find(collection_name)).get_between_keys(min_key, max_key);

        std::cout << "[DATA BASE] received values from " << pool_name << " " << scheme_name << " " << collection_name << std::endl << std::endl;

        int index = 1;

        for (auto const & data_value : data)
        {
            std::cout << "\tData:" << index << std::endl;

            std::cout << "surname: " << data_value->_surname << std::endl;
            std::cout << "name: " << data_value->_name << std::endl;
            std::cout << "patronymic: " << data_value->_patronymic << std::endl;
            std::cout << "date: " << data_value->_date << std::endl;
            std::cout << "time: " << data_value->_time << std::endl;
            std::cout << "mark: " << data_value->_mark << std::endl;

            index++;
        }

        return data;
    }
    catch (std::exception const &ex)
    {
        std::cout << ex.what() << std::endl;
    }
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
    try
    {
        const_cast<data_collection &>(
                _data_base
                ->find(pool_name)
                .find(scheme_name)
                .find(collection_name)).update(id_session, id_student, format, subject, surname, name, patronymic, data, time, mark);

        std::cout << "[DATA BASE] " << "data from " << pool_name << " " << scheme_name << " " << collection_name <<  " updated" << std::endl << std::endl;
    }
    catch (std::exception const &ex)
    {
        std::cout << ex.what() << std::endl;
    }
}

data_base *data_base::get_instance()
{
    if (_instance == nullptr)
    {
        _instance = new data_base();
    }

    return _instance;
}

void data_base::handle_request(
        std::string const &request)
{
    _chain.handle(request);
}