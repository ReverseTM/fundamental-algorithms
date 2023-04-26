#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "associative_container.h"
#include "../logger/logger.h"
#include "../logger/logger_holder.h"
#include "../memory_allocators/memory.h"
#include "../memory_allocators/memory_holder.h"
#include <vector>
#include <stack>

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
class binary_search_tree :
        public associative_container<tkey, tvalue>,
        protected logger_holder,
        protected memory_holder
{

protected:

    struct node
    {
        typename associative_container<tkey, tvalue>::key_value_pair key_and_value;

        node *left_subtree_address;

        node *right_subtree_address;

    };

public:

    class prefix_iterator final
    {

    private:

        node *_tree_root;
        std::stack<node *> _way;

    public:

        explicit prefix_iterator(node *tree_root);

    public:

        bool operator==(prefix_iterator const &other) const;

        prefix_iterator& operator++();

        prefix_iterator operator++(int not_used);

        std::tuple<unsigned int, tkey const&, tvalue const&> operator*() const;

    };

    class infix_iterator final
    {

    private:

        node *_tree_root;
        std::stack<node *> _way;

    public:

        explicit infix_iterator(node *tree_root);

    public:

        bool operator==(infix_iterator const &other) const;

        infix_iterator& operator++();

        infix_iterator operator++(int not_used);

        std::tuple<unsigned int, tkey const&, tvalue const&> operator*() const;

    };

    class postfix_iterator final
    {

    private:

        node *_tree_root;
        std::stack<node *> _way;

    public:

        explicit postfix_iterator(node *tree_root);

    public:

        bool operator==(postfix_iterator const &other) const;

        postfix_iterator &operator++();

        postfix_iterator operator++(int not_used);

        std::tuple<unsigned int, tkey const&, tvalue const&> operator*() const;

    };

protected:

    class insertion_template_method : protected logger_holder, protected memory_holder
    {

    private:

        binary_search_tree<tkey, tvalue, tkey_comparer> * _tree;

    public:

        explicit insertion_template_method(binary_search_tree<tkey, tvalue, tkey_comparer> *tree);

    public:

        virtual ~insertion_template_method() = default;

    public:

        void insert(
            tkey const &key,
            tvalue &&value,
            node *&subtree_root_address);

    private:

        void insert_inner(
            tkey const &key,
            tvalue &&value,
            node *&subtree_root_address,
            std::stack<node **> &path_to_subtree_root_exclusive);

    protected:

        virtual void before_insert_inner(
            tkey const &key,
            node *&subtree_root_address,
            std::stack<node **> &path_to_subtree_root_exclusive);

        virtual void after_insert_inner(
            tkey const &key,
            node *&subtree_root_address,
            std::stack<node **> &path_to_subtree_root_exclusive);

        virtual void initialize_memory_with_node(binary_search_tree<tkey, tvalue, tkey_comparer>::node * const node_address);


    private:

        fund_alg::logger * get_logger() const override
        {
            return _tree->_logger;
        }

        memory * get_outer_allocator() const override
        {
            return _tree->_allocator;
        }

        virtual size_t get_node_size() const
        {
            return sizeof(node);
        }
    };

    class reading_template_method
    {

    public:

        virtual ~reading_template_method() = default;

    public:

        bool read(
            typename associative_container<tkey, tvalue>::key_value_pair * target_key_and_result_value,
            node *&subtree_root_address);

    private:

        bool read_inner(
            typename associative_container<tkey, tvalue>::key_value_pair * target_key_and_result_value,
            node *&subtree_root_address,
            std::stack<node **> &path_to_subtree_root_exclusive);

    protected:

        virtual void before_read_inner(
            typename associative_container<tkey, tvalue>::key_value_pair * target_key_and_result_value,
            node *&subtree_root_address,
            std::stack<node **> &path_to_subtree_root_exclusive);

        virtual void after_read_inner(
            typename associative_container<tkey, tvalue>::key_value_pair * target_key_and_result_value,
            node *&subtree_root_address,
            std::stack<node **> &path_to_subtree_root_exclusive);

    };

    class removing_template_method : protected logger_holder, protected memory_holder
    {

    private:

        binary_search_tree<tkey, tvalue, tkey_comparer> * _tree;

    public:

        explicit removing_template_method(binary_search_tree<tkey, tvalue, tkey_comparer> *tree);

    public:

        virtual ~removing_template_method() = default;

    public:

        tvalue &&remove(
            tkey const &key,
            node *&tree_root_address);

    private:

        tvalue &&remove_inner(
            tkey const &key,
            node *&subtree_root_address,
            std::stack<node **> &path_to_subtree_root_exclusive);

    protected:

        virtual void before_remove_inner(
            tkey const &key,
            node *&subtree_root_address,
            std::stack<node **> &path_to_subtree_root_exclusive);

        virtual void after_remove_inner(
            tkey const &key,
            node *&subtree_root_address,
            std::stack<node **> &path_to_subtree_root_exclusive);

    private:

        fund_alg::logger * get_logger() const override
        {
            return _tree->_logger;
        }

        memory * get_outer_allocator() const override
        {
            return _tree->_allocator;
        }
    };

private:

    node *_root;
    memory *_allocator;
    fund_alg::logger *_logger;
    tkey_comparer _comparator;
    insertion_template_method *_insertion;
    reading_template_method *_reading;
    removing_template_method *_removing;

protected:

    explicit binary_search_tree(
        insertion_template_method *insertion,
        reading_template_method *reading,
        removing_template_method *removing,
        memory *allocator = nullptr,
        fund_alg::logger *logger = nullptr);

public:

    explicit binary_search_tree(
        memory *allocator = nullptr,
        fund_alg::logger *logger = nullptr);

    binary_search_tree(
        binary_search_tree const &other);

    binary_search_tree(
        binary_search_tree &&other) noexcept;

    binary_search_tree &operator=(
        binary_search_tree const &other);

    binary_search_tree &operator=(
        binary_search_tree &&other) noexcept;

    ~binary_search_tree();

public:

    void insert(tkey const &key, tvalue &&value) override final;

    bool find(typename associative_container<tkey, tvalue>::key_value_pair * target_key_and_result_value) override final;

    tvalue &&remove(tkey const &key) override final;

private:

    std::string get_typename() const;

private:

    memory * get_outer_allocator() const override;

    fund_alg::logger * get_logger() const override;

public:

    prefix_iterator begin_prefix() const noexcept;

    prefix_iterator end_prefix() const noexcept;

    infix_iterator begin_infix() const noexcept;

    infix_iterator end_infix() const noexcept;

    postfix_iterator begin_postfix() const noexcept;

    postfix_iterator end_postfix() const noexcept;


protected:

    virtual void right_rotation(node *&subtree_root) const;

    virtual void left_rotation(node *&subtree_root) const;

};

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
        void binary_search_tree<tkey, tvalue, tkey_comparer>::left_rotation(node *&subtree_root) const
{
            node *tmp = subtree_root;
            subtree_root = subtree_root->right_subtree_address;
            tmp->right_subtree_address = subtree_root->left_subtree_address;
            subtree_root->left_subtree_address = tmp;
}

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
        void binary_search_tree<tkey, tvalue, tkey_comparer>::right_rotation(node *&subtree_root) const
{
            node *tmp = subtree_root;
            subtree_root = subtree_root->left_subtree_address;
            tmp->left_subtree_address = subtree_root->right_subtree_address;
            subtree_root->right_subtree_address = tmp;
}
// region iterators implementation

//region prefix_iterator implementation

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
binary_search_tree<tkey, tvalue, tkey_comparer>::prefix_iterator::prefix_iterator(
    binary_search_tree<tkey, tvalue, tkey_comparer>::node *tree_root)
{

}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
bool binary_search_tree<tkey, tvalue, tkey_comparer>::prefix_iterator::operator==(
    binary_search_tree<tkey, tvalue, tkey_comparer>::prefix_iterator const &other) const
{

}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
typename binary_search_tree<tkey, tvalue, tkey_comparer>::prefix_iterator &binary_search_tree<tkey, tvalue, tkey_comparer>::prefix_iterator::operator++()
{

}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
typename binary_search_tree<tkey, tvalue, tkey_comparer>::prefix_iterator binary_search_tree<tkey, tvalue, tkey_comparer>::prefix_iterator::operator++(
    int not_used)
{

}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
std::tuple<unsigned int, tkey const&, tvalue const&> binary_search_tree<tkey, tvalue, tkey_comparer>::prefix_iterator::operator*() const
{

}

//endregion prefix_iterator implementation

//region infix_iterator implementation

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
binary_search_tree<tkey, tvalue, tkey_comparer>::infix_iterator::infix_iterator(
    binary_search_tree<tkey, tvalue, tkey_comparer>::node *tree_root)
{

}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
bool binary_search_tree<tkey, tvalue, tkey_comparer>::infix_iterator::operator==(
    binary_search_tree<tkey, tvalue, tkey_comparer>::infix_iterator const &other) const
{

}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
typename binary_search_tree<tkey, tvalue, tkey_comparer>::infix_iterator &binary_search_tree<tkey, tvalue, tkey_comparer>::infix_iterator::operator++()
{

}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
typename binary_search_tree<tkey, tvalue, tkey_comparer>::infix_iterator binary_search_tree<tkey, tvalue, tkey_comparer>::infix_iterator::operator++(
    int not_used)
{

}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
std::tuple<unsigned int, tkey const&, tvalue const&> binary_search_tree<tkey, tvalue, tkey_comparer>::infix_iterator::operator*() const
{

}

//endregion infix_iterator implementation

//region postfix_iterator implementation

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
binary_search_tree<tkey, tvalue, tkey_comparer>::postfix_iterator::postfix_iterator(
    binary_search_tree<tkey, tvalue, tkey_comparer>::node *tree_root)
{

}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
bool binary_search_tree<tkey, tvalue, tkey_comparer>::postfix_iterator::operator==(
    binary_search_tree<tkey, tvalue, tkey_comparer>::postfix_iterator const &other) const
{

}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
typename binary_search_tree<tkey, tvalue, tkey_comparer>::postfix_iterator &binary_search_tree<tkey, tvalue, tkey_comparer>::postfix_iterator::operator++()
{

}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
typename binary_search_tree<tkey, tvalue, tkey_comparer>::postfix_iterator binary_search_tree<tkey, tvalue, tkey_comparer>::postfix_iterator::operator++(
    int not_used)
{

}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
std::tuple<unsigned int, tkey const&, tvalue const&> binary_search_tree<tkey, tvalue, tkey_comparer>::postfix_iterator::operator*() const
{

}

//endregion prefix_iterator implementation

// endregion iterators implementation

// region template methods implementation

// region insertion implementation

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::insertion_template_method::initialize_memory_with_node(
        binary_search_tree<tkey, tvalue, tkey_comparer>::node * const node_address)
{
    new (node_address) binary_search_tree<tkey, tvalue, tkey_comparer>::node;
}


template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::insertion_template_method::insert(
    tkey const &key,
    tvalue &&value,
    node *&subtree_root_address)
{
    std::stack<binary_search_tree<tkey, tvalue, tkey_comparer>::node **> path_to_subtree_root_exclusive;

    return insert_inner(key, std::move(value), subtree_root_address, path_to_subtree_root_exclusive);
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::insertion_template_method::insert_inner(
    tkey const &key,
    tvalue &&value,
    binary_search_tree<tkey, tvalue, tkey_comparer>::node *&subtree_root_address,
    std::stack<binary_search_tree<tkey, tvalue, tkey_comparer>::node **> &path_to_subtree_root_exclusive)
{
    if (subtree_root_address == nullptr)
    {
        subtree_root_address = reinterpret_cast<node*>(this->allocate_with_guard(get_node_size()));

        this->initialize_memory_with_node(subtree_root_address);

        subtree_root_address->key_and_value._key = key;
        subtree_root_address->key_and_value._value = std::move(value);
        subtree_root_address->left_subtree_address = nullptr;
        subtree_root_address->right_subtree_address = nullptr;
    }
    else
    {
        if (_tree->_comparator(key, subtree_root_address->key_and_value._key) == 0)
        {
            throw "Gde labi";
        }

        path_to_subtree_root_exclusive.push(&subtree_root_address);

        if (_tree->_comparator(key, subtree_root_address->key_and_value._key) > 0)
        {
            insert_inner(key, std::move(value), subtree_root_address->right_subtree_address, path_to_subtree_root_exclusive);
        }
        else
        {
            insert_inner(key, std::move(value), subtree_root_address->left_subtree_address, path_to_subtree_root_exclusive);
        }
    }

    after_insert_inner(key, subtree_root_address, path_to_subtree_root_exclusive);
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::insertion_template_method::before_insert_inner(
    tkey const &key,
    binary_search_tree<tkey, tvalue, tkey_comparer>::node *&subtree_root_address,
    std::stack<binary_search_tree<tkey, tvalue, tkey_comparer>::node **> &path_to_subtree_root_exclusive)
{

}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::insertion_template_method::after_insert_inner(
    tkey const &key,
    binary_search_tree<tkey, tvalue, tkey_comparer>::node *&subtree_root_address,
    std::stack<binary_search_tree<tkey, tvalue, tkey_comparer>::node **> &path_to_subtree_root_exclusive)
{

}

// endregion insertion implementation

// region reading implementation

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
bool binary_search_tree<tkey, tvalue, tkey_comparer>::reading_template_method::read(
    typename associative_container<tkey, tvalue>::key_value_pair * target_key_and_result_value,
    node *&tree_root_address)
{
    std::stack<node **> path_to_subtree_root_exclusive;

    return read_inner(target_key_and_result_value, tree_root_address, path_to_subtree_root_exclusive);
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
bool binary_search_tree<tkey, tvalue, tkey_comparer>::reading_template_method::read_inner(
    typename associative_container<tkey, tvalue>::key_value_pair * target_key_and_result_value,
    node *&subtree_root_address,
    std::stack<node **> &path_to_subtree_root_exclusive)
{
    if (subtree_root_address == nullptr)
    {
        return false;
    }

    tkey_comparer comparator;

    int comparator_result = comparator(target_key_and_result_value->_key, subtree_root_address->key_and_value._key);

    bool result_method = false;

    if (comparator_result == 0)
    {
        target_key_and_result_value->_value = subtree_root_address->key_and_value._value;
        return true;
    }

    path_to_subtree_root_exclusive.push(&subtree_root_address);

    if (comparator_result < 0)
    {
        result_method = read_inner(target_key_and_result_value, subtree_root_address->left_subtree_address, path_to_subtree_root_exclusive);
    }
    else
    {
        result_method = read_inner(target_key_and_result_value, subtree_root_address->right_subtree_address, path_to_subtree_root_exclusive);
    }

    path_to_subtree_root_exclusive.pop();

    after_read_inner(target_key_and_result_value, subtree_root_address, path_to_subtree_root_exclusive);

    return result_method;
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::reading_template_method::before_read_inner(
    typename associative_container<tkey, tvalue>::key_value_pair * target_key_and_result_value,
    binary_search_tree<tkey, tvalue, tkey_comparer>::node *&subtree_root_address,
    std::stack<binary_search_tree<tkey, tvalue, tkey_comparer>::node **> &path_to_subtree_root_exclusive)
{

}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::reading_template_method::after_read_inner(
    typename associative_container<tkey, tvalue>::key_value_pair * target_key_and_result_value,
    binary_search_tree<tkey, tvalue, tkey_comparer>::node *&subtree_root_address,
    std::stack<binary_search_tree<tkey, tvalue, tkey_comparer>::node **> &path_to_subtree_root_exclusive)
{

}

// endregion reading implementation

// region removing implementation

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
tvalue &&binary_search_tree<tkey, tvalue, tkey_comparer>::removing_template_method::remove(
    tkey const &key,
    binary_search_tree<tkey, tvalue, tkey_comparer>::node *&tree_root_address)
{
    std::stack<binary_search_tree<tkey, tvalue, tkey_comparer>::node **> path_to_subtree_root_exclusive;

    return std::move(remove_inner(key, tree_root_address, path_to_subtree_root_exclusive));
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
tvalue &&binary_search_tree<tkey, tvalue, tkey_comparer>::removing_template_method::remove_inner(
    tkey const &key,
    binary_search_tree<tkey, tvalue, tkey_comparer>::node *&subtree_root_address,
    std::stack<binary_search_tree<tkey, tvalue, tkey_comparer>::node **> &path_to_subtree_root_exclusive)
{
    before_remove_inner(key, subtree_root_address, path_to_subtree_root_exclusive); //not used



    after_remove_inner(key, subtree_root_address, path_to_subtree_root_exclusive);
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::removing_template_method::before_remove_inner(
    tkey const &key,
    binary_search_tree<tkey, tvalue, tkey_comparer>::node *&subtree_root_address,
    std::stack<binary_search_tree<tkey, tvalue, tkey_comparer>::node **> &path_to_subtree_root_exclusive)
{

}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::removing_template_method::after_remove_inner(
    tkey const &key,
    binary_search_tree<tkey, tvalue, tkey_comparer>::node *&subtree_root_address,
    std::stack<binary_search_tree<tkey, tvalue, tkey_comparer>::node **> &path_to_subtree_root_exclusive)
{

}

// endregion implementation

// endregion template methods

// region construction, assignment, destruction implementation

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
binary_search_tree<tkey, tvalue, tkey_comparer>::insertion_template_method::insertion_template_method(
        binary_search_tree<tkey, tvalue, tkey_comparer> *tree):
        _tree(tree)
{

}

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
binary_search_tree<tkey, tvalue, tkey_comparer>::removing_template_method::removing_template_method(
        binary_search_tree<tkey, tvalue, tkey_comparer> *tree):
        _tree(tree)
{

}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
binary_search_tree<tkey, tvalue, tkey_comparer>::binary_search_tree(
    binary_search_tree::insertion_template_method *insertion,
    binary_search_tree::reading_template_method *reading,
    binary_search_tree::removing_template_method *removing,
    memory *allocator,
    fund_alg::logger *logger):
    _comparator(),
    _root(nullptr),
    _insertion(insertion),
    _reading(reading),
    _removing(removing),
    _allocator(allocator),
    _logger(logger)
{

}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
binary_search_tree<tkey, tvalue, tkey_comparer>::binary_search_tree(
    memory *allocator,
    fund_alg::logger *logger):
    _comparator(),
    _insertion(new insertion_template_method(this)),
    _reading(new reading_template_method()),
    _removing(new removing_template_method(this)),
    _allocator(allocator),
    _logger(logger),
    _root(nullptr)
{

}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
binary_search_tree<tkey, tvalue, tkey_comparer>::binary_search_tree(
    const binary_search_tree &other)
{

}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
binary_search_tree<tkey, tvalue, tkey_comparer>::binary_search_tree(
    binary_search_tree &&other) noexcept
{
    // TODO
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
binary_search_tree<tkey, tvalue, tkey_comparer> &binary_search_tree<tkey, tvalue, tkey_comparer>::operator=(
    const binary_search_tree &other)
{
    if (this == &other)
    {
        return *this;
    }



    return *this;
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
binary_search_tree<tkey, tvalue, tkey_comparer> &binary_search_tree<tkey, tvalue, tkey_comparer>::operator=(
    binary_search_tree &&other) noexcept
{
    if (this == &other)
    {
        return *this;
    }



    return *this;
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
binary_search_tree<tkey, tvalue, tkey_comparer>::~binary_search_tree()
{
    // TODO: remove all elements

    delete _insertion;
    delete _reading;
    delete _removing;
}

// endregion construction, assignment, destruction implementation

// region associative_container contract implementation

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::insert(tkey const &key,tvalue &&value)
{
    return _insertion->insert(key, std::move(value), _root);
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
bool binary_search_tree<tkey, tvalue, tkey_comparer>::find(typename associative_container<tkey, tvalue>::key_value_pair * target_key_and_result_value)
{
    return _reading->read(target_key_and_result_value, _root);
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
tvalue &&binary_search_tree<tkey, tvalue, tkey_comparer>::remove(tkey const &key)
{
    return std::move(_removing->remove(key, _root));
}

// endregion associative_container contract implementation

// region logger_holder contract implementation

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
fund_alg::logger *binary_search_tree<tkey, tvalue, tkey_comparer>::get_logger() const
{
    return _logger;
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
memory * binary_search_tree<tkey, tvalue, tkey_comparer>::get_outer_allocator() const
{
    return _allocator;
}

template<
     typename tkey,
     typename tvalue,
     typename tkey_comparer>
std::string binary_search_tree<tkey, tvalue, tkey_comparer>::get_typename() const
{
    auto tkey_typename = typeid(tkey).name();
    auto tvalue_typename = typeid(tvalue).name();
    auto tkey_comparer_typename = typeid(tkey_comparer).name();

    return std::string("binary_search_tree<") + tkey_typename + ", " + tvalue_typename + ", " + tkey_comparer_typename + ">";
}

// endregion logger_holder contract implementation

// region iterators requesting implementation

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
typename binary_search_tree<tkey, tvalue, tkey_comparer>::prefix_iterator binary_search_tree<tkey, tvalue, tkey_comparer>::begin_prefix() const noexcept
{

}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
typename binary_search_tree<tkey, tvalue, tkey_comparer>::prefix_iterator binary_search_tree<tkey, tvalue, tkey_comparer>::end_prefix() const noexcept
{

}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
typename binary_search_tree<tkey, tvalue, tkey_comparer>::infix_iterator binary_search_tree<tkey, tvalue, tkey_comparer>::begin_infix() const noexcept
{

}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
typename binary_search_tree<tkey, tvalue, tkey_comparer>::infix_iterator binary_search_tree<tkey, tvalue, tkey_comparer>::end_infix() const noexcept
{

}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
typename binary_search_tree<tkey, tvalue, tkey_comparer>::postfix_iterator binary_search_tree<tkey, tvalue, tkey_comparer>::begin_postfix() const noexcept
{

}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
typename binary_search_tree<tkey, tvalue, tkey_comparer>::postfix_iterator binary_search_tree<tkey, tvalue, tkey_comparer>::end_postfix() const noexcept
{

}

// endregion iterators requesting implementation

#endif //BINARY_SEARCH_TREE_H
