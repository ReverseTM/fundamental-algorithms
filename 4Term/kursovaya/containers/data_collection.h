#ifndef DATA_COLLECTION_H
#define DATA_COLLECTION_H

#include "../types/data_type.h"
#include "../compare/string_comparer.h"
#include "../compare/key_comparator.h"
#include "../memory_allocators/memory.h"
#include "../memory_allocators/global_heap_allocator.h"
#include "../memory_allocators/sorted_list_allocator.h"
#include "../memory_allocators/border_descriptors_allocator.h"
#include "../memory_allocators/buddy_allocator.h"
#include "../tree/binary_search_tree.h"
#include "../tree/splay_tree.h"

class data_collection final : protected memory_holder
{

private:

    memory * _allocator;

    associative_container<key*, value*> * _data;

public:

    data_collection(memory * allocator = nullptr);

    ~data_collection();

public:

    void add(
            unsigned int id_session,
            unsigned int id_student,
            form format,
            const std::string &subject,
            const std::string &surname,
            const std::string &name,
            const std::string &patronymic,
            const std::string &date,
            const std::string &time,
            unsigned int mark);

    bool find_in(key * const & data_key) const;

    value remove(key * data_key);

    value * get(key * const & data_key);

    std::vector<value *> get_between_keys(key * const & min_key, key * const & max_key);

    void update(
            key *const &data_key,
            const std::string & surname,
            const std::string & name,
            const std::string & patronymic,
            const std::string & date,
            const std::string & time,
            unsigned int mark);

public:

    data_collection(data_collection const & other);

    data_collection & operator=(data_collection const & other);

    data_collection(data_collection && other) noexcept;

    data_collection & operator=(data_collection && other) noexcept;

private:

    memory * get_outer_allocator() const override;

};


#endif //DATA_COLLECTION_H
