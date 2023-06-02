#ifndef DATA_BASE_H
#define DATA_BASE_H

#include "../logger/logger_implementation.h"
#include "../logger/builder_implementation.h"
#include "../memory_allocators/memory.h"
#include "../memory_allocators/global_heap_allocator.h"
#include "../memory_allocators/sorted_list_allocator.h"
#include "../memory_allocators/border_descriptors_allocator.h"
#include "../memory_allocators/buddy_allocator.h"
#include "../tree/binary_search_tree.h"
#include "../tree/splay_tree.h"
#include "pool.h"
#include "scheme.h"
#include "data_collection.h"
#include <fstream>

class data_base
{

private:

    associative_container<std::string, std::pair<pool*, memory*>> * _data_base;

public:

    enum class allocators
    {
        LIST,
        BORDER,
        BUDDIES
    };

public:

    void read_file(std::string & file_name);

    void dialog();

    explicit data_base();

    ~data_base();

private:

    void parse(std::string & command);

private:

    void add_pool(std::string & name, allocators allocator_name, size_t request_size, memory::allocation_mode mode);

    void add_scheme(std::string & pool_name, std::string & scheme_name);

    void add_collection(std::string & pool_name, std::string & scheme_name, std::string & collection_name);

public:

    data_base(data_base const & other) = delete;

    data_base & operator=(data_base const & other) = delete;

    data_base(data_base && other) = delete;

    data_base & operator=(data_base && other) = delete;

};


#endif //DATA_BASE_H
