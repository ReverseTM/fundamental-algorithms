#include "data_base.h"
#include <cmath>

data_base::data_base(): _data_base(new splay_tree<std::string, std::pair<pool*, memory*>, key_comparer>()) {}

data_base::~data_base()
{
    delete _data_base;
}

void data_base::read_file(std::string & file_name)
{

    add_pool((std::string &)"pool_1", allocators::LIST, 1000000, memory::allocation_mode::first_match);
//    std::ifstream file(file_name);
//    std::string command;
//
//    while (std::getline(file, command))
//    {
//        parse(command);
//    }
}

void data_base::parse(std::string & command)
{

}

void data_base::add_pool(std::string & name, allocators allocator_name, size_t request_size, memory::allocation_mode mode)
{
    memory * allocator = nullptr;

    if (allocator_name == allocators::LIST)
    {
        allocator = new sorted_list_allocator(request_size, mode);
    }
    else if (allocator_name == allocators::BORDER)
    {
        allocator = new border_descriptors_allocator(request_size, mode);
    }
    else
    {
        request_size = static_cast<int>(log2(request_size)) + 1;
        allocator = new buddy_system_allocator(request_size, mode);
    }

    pool * current_pool = reinterpret_cast<pool*>(allocator->allocate(sizeof(pool)));

    new (current_pool) pool;

    _data_base->insert(name, std::move(std::make_pair(current_pool, allocator)));
}

void data_base::add_scheme(std::string &pool_name, std::string &scheme_name)
{
    associative_container<std::string, std::pair<pool*, memory*>>::key_value_pair pair{pool_name};

    if (_data_base->find(&pair))
    {
        auto current_pool = pair._value.first;
        auto allocator = pair._value.second;

        scheme * current_scheme = reinterpret_cast<scheme*>(allocator->allocate(sizeof(scheme)));

        new (current_scheme) scheme;

        current_pool->_pool->insert(scheme_name, std::move(current_scheme));

    }
}

void data_base::add_collection(std::string &pool_name, std::string &scheme_name, std::string &collection_name)
{
    associative_container<std::string, std::pair<pool*, memory*>>::key_value_pair pair_pool{pool_name};

    if (_data_base->find(&pair_pool))
    {
        auto allocator = pair_pool._value.second;
        auto current_pool = pair_pool._value.first;

        associative_container<std::string, scheme*>::key_value_pair pair_scheme{scheme_name};

        if (current_pool->_pool->find(&pair_scheme))
        {
            auto current_scheme = pair_scheme._value;

            data_collection * current_collection = reinterpret_cast<data_collection*>(allocator->allocate(sizeof(data_collection)));

            new (current_collection) data_collection;

            current_scheme->_scheme->insert(collection_name, std::move(current_collection));
        }
    }
}