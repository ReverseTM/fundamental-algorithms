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

data_collection const & scheme::find(std::string const & collection_name) const
{
    return _scheme->find(collection_name);
}

bool scheme::find_in(std::string const & collection_name) const
{
    return _scheme->find_in(collection_name);
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