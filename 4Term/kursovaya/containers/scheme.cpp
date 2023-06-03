#include "scheme.h"

scheme::scheme(): _scheme(new splay_tree<std::string, data_collection, string_comparer>()) {}

void scheme::add(const std::string & key, data_collection && target)
{
    _scheme->insert(key, std::move(target));
}

void scheme::remove(const std::string & key)
{
    _scheme->remove(key);
}

bool scheme::find(associative_container<std::string, data_collection>::key_value_pair * target_key_and_value)
{
    return _scheme->find(target_key_and_value);
}

scheme::scheme(const scheme & other)
    : _scheme(new splay_tree<std::string, data_collection, string_comparer>(*reinterpret_cast<splay_tree<std::string, data_collection, string_comparer>*>(other._scheme)))
{

}

scheme::scheme(scheme && other) noexcept
{
    this->_scheme = other._scheme;
    other._scheme = nullptr;
}

scheme &scheme::operator=(const scheme & other)
{
    if (this == &other)
    {
        return *this;
    }

    delete this->_scheme;

    this->_scheme = new splay_tree<std::string, data_collection, string_comparer>(*reinterpret_cast<splay_tree<std::string, data_collection, string_comparer>*>(other._scheme));

    return *this;
}

scheme &scheme::operator=(scheme && other) noexcept
{
    if (this == &other)
    {
        return *this;
    }

    delete this->_scheme;

    this->_scheme = other._scheme;

    other._scheme = nullptr;

    return *this;
}

scheme::~scheme()
{
    delete _scheme;
}