#ifndef DATA_BASE_H
#define DATA_BASE_H

#include "pool.h"
#include "../types/allocator_types.h"
#include "../request_handler_with_command_chain/request_handler_with_command_chain.h"

class data_base
{

private:

    static data_base * _instance;

private:

    request_handler_with_command_chain _chain;

private:

    associative_container<std::string, pool>  * _data_base;

public:

    data_base();

    ~data_base();

public:

    static data_base *get_instance();

public:

    void add_pool(std::string const & name_pool, allocator_types allocator_name, size_t request_size, memory::allocation_mode mode);

    void add_scheme(std::string const & pool_name, std::string const & scheme_name);

    void add_collection(std::string const & pool_name, std::string const & scheme_name, std::string const & collection_name);

    void add_data(std::string const & pool_name,
         std::string const & scheme_name,
         std::string const & collection_name,
         unsigned int id_session,
         unsigned int id_student,
         form format,
         std::string const & subject,
         std::string const & surname,
         std::string const & name,
         std::string const & patronymic,
         std::string const & date,
         std::string const & time,
         unsigned int mark
         );

    void remove_pool(std::string const & name);

    void remove_scheme(std::string const & pool_name, std::string const & scheme_name);

    void remove_collection(std::string const & pool_name, std::string const & scheme_name, std::string const & collection_name);

    void remove_data(
            std::string const & pool_name,
            std::string const & scheme_name,
            std::string const & collection_name,
            key * data_key);

    void update_data(
            std::string const & pool_name,
            std::string const & scheme_name,
            std::string const & collection_name,
            key * const & data_key,
            std::string const & surname,
            std::string const & name,
            std::string const & patronymic,
            std::string const & date,
            std::string const & time,
            unsigned int mark);

    void get_data(std::string const & pool_name, std::string const & scheme_name, std::string const & collection_name, key * const & data_key);

    void get_data_between_keys(std::string const & pool_name, std::string const & scheme_name, std::string const & collection_name, key * const & min_key, key * const & max_key);

public:

    void handle_request(
            std::string const &request);

public:

    data_base(data_base const & other) = delete;

    data_base & operator=(data_base const & other) = delete;

    data_base(data_base && other) = delete;

    data_base & operator=(data_base && other) = delete;

};

#endif //DATA_BASE_H
