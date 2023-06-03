#ifndef DATA_BASE_H
#define DATA_BASE_H

#include "pool.h"


class data_base
{

private:

    associative_container<std::string, pool>  * _data_base;

public:

    enum class allocators
    {
        GLOBAL_HEAP,
        SORTED_LIST,
        BORDER_DESCRIPTORS,
        BUDDIES_SYSTEM
    };

public:

    explicit data_base();

    ~data_base();


public:

    void add_pool(std::string const & name_pool, allocators allocator_name, size_t request_size, memory::allocation_mode mode);

    void add_scheme(std::string const & pool_name, std::string const & scheme_name);

    void add_collection(std::string const & pool_name, std::string const & scheme_name, std::string const & collection_name);

    void add_data(std::string const & pool_name,
         std::string const & scheme_name,
         std::string const & collection_name,
         unsigned int id_session,
         unsigned int id_student,
         std::string const & format,
         std::string const & subject,
         std::string const & surname,
         std::string const & name,
         std::string const & patronymic,
         std::string const & data,
         std::string const & time,
         unsigned int mark
         );

    void remove_pool(std::string const & name);

    void remove_scheme(std::string const & pool_name, std::string const & scheme_name);

    void remove_collection(std::string const & pool_name, std::string const & scheme_name, std::string const & collection_name);

    value remove_data(
            std::string const & pool_name,
            std::string const & scheme_name,
            std::string const & collection_name,
            key * data_key);

public:

    data_base(data_base const & other) = delete;

    data_base & operator=(data_base const & other) = delete;

    data_base(data_base && other) = delete;

    data_base & operator=(data_base && other) = delete;

};


#endif //DATA_BASE_H
