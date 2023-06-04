#include "data_collection.h"

data_collection::data_collection(memory * allocator): _data(new splay_tree<key*, value*, key_comparer>(allocator, nullptr)), _allocator(allocator)
{

}

void data_collection::add(
        unsigned int id_session,
        unsigned int id_student,
        form format,
        const std::string &subject,
        const std::string &surname,
        const std::string &name,
        const std::string &patronymic,
        const std::string &date,
        const std::string &time,
        unsigned int mark)
{
    key * data_key = reinterpret_cast<key*>(allocate_with_guard(sizeof(key)));
    new (data_key) key;

    data_key->_id_session = id_session;
    data_key->_id_student = id_student;
    data_key->_format = format;
    data_key->_subject = subject;

    value * data_value = reinterpret_cast<value*>(allocate_with_guard(sizeof(value)));
    new (data_value) value;

    data_value->_surname = surname;
    data_value->_name = name;
    data_value->_patronymic = patronymic;
    data_value->_date = date;
    data_value->_time = time;
    data_value->_mark = mark;

    _data->insert(data_key, std::move(data_value));
}

value data_collection::remove(key * data_key)
{
    value * returned_value = _data->remove(data_key);

    value result = *returned_value;

    returned_value->~value();
    deallocate_with_guard(returned_value);

    return result;
}

value * data_collection::get(key * const & data_key)
{
    return _data->get_value(data_key);
}

std::vector<value *> data_collection::get_between_keys(key *const &min_key, key *const &max_key)
{
    return _data->find_in_range(min_key, max_key);
}

void data_collection::update(
        unsigned int id_session,
        unsigned int id_student,
        form format,
        const std::string & subject,
        const std::string & surname,
        const std::string & name,
        const std::string & patronymic,
        const std::string & date,
        const std::string & time,
        unsigned int mark)
{
    key * data_key = reinterpret_cast<key*>(allocate_with_guard(sizeof(key)));
    new (data_key) key;

    data_key->_id_session = id_session;
    data_key->_id_student = id_student;
    data_key->_format = format;
    data_key->_subject = subject;

    value * data_value = reinterpret_cast<value*>(allocate_with_guard(sizeof(value)));
    new (data_value) value;

    data_value->_surname = surname;
    data_value->_name = name;
    data_value->_patronymic = patronymic;
    data_value->_date = date;
    data_value->_time = time;
    data_value->_mark = mark;

    _data->update(data_key, std::move(data_value));

    data_key->~key();
    deallocate_with_guard(data_key);
}

memory * data_collection::get_outer_allocator() const
{
    return _allocator;
}

data_collection::data_collection(const data_collection &other)
    : _data(new splay_tree<key*, value*, key_comparer>(*reinterpret_cast<splay_tree<key*, value*, key_comparer>*>(other._data))), _allocator(other._allocator)
{

}

data_collection::data_collection(data_collection &&other) noexcept
{
    this->_data = other._data;
    this->_allocator = other._allocator;

    other._data = nullptr;
    other._allocator = nullptr;
}

data_collection &data_collection::operator=(const data_collection &other)
{
    if (this == &other)
    {
        return *this;
    }

    delete this->_data;

    if (this->_allocator != other._allocator)
    {
        delete this->_allocator;
        this->_allocator = other._allocator;
    }

    this->_data = new splay_tree<key*, value*, key_comparer>(*reinterpret_cast<splay_tree<key*, value*, key_comparer>*>(other._data));

    return *this;
}

data_collection &data_collection::operator=(data_collection &&other) noexcept
{
    if (this == &other)
    {
        return *this;
    }

    delete this->_data;
    delete this->_allocator;

    this->_data = other._data;
    this->_allocator = other._allocator;

    other._data = nullptr;
    other._allocator = nullptr;

    return *this;
}

data_collection::~data_collection()
{
    delete _data;
    delete _allocator;
}