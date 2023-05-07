#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "associative_container.h"
#include "../logger/logger.h"
#include "../logger/logger_holder.h"
#include "../memory_allocators/memory.h"
#include "../memory_allocators/memory_holder.h"
#include <vector>
#include <stack>
#include <sstream>
#include <list>

template <typename T>
std::string to_string(T str)
{
    return std::string { (std::stringstream () << str).str() };
}

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

    public:

        virtual ~node() = default;

    };

public:

    class prefix_iterator final
    {

    private:

        node * _current_node;
        std::stack<node *> _way;

    public:

        explicit prefix_iterator(node *tree_root);

    public:

        bool operator==(prefix_iterator const &other) const;

        bool operator!=(prefix_iterator const &other) const;

        prefix_iterator& operator++();

        prefix_iterator operator++(int not_used);

        std::tuple<unsigned int, tkey const&, tvalue const&> operator*() const;

    };

    class infix_iterator final
    {

    private:

        node * _current_node;
        std::stack<node *> _way;

    public:

        explicit infix_iterator(node *tree_root);

    public:

        bool operator==(infix_iterator const &other) const;

        bool operator!=(infix_iterator const &other) const;

        infix_iterator& operator++();

        infix_iterator operator++(int not_used);

        std::tuple<unsigned int, tkey const&, tvalue const&> operator*() const;

    };

    class postfix_iterator final
    {

        friend class binary_search_tree<tkey, tvalue, tkey_comparer>;

    private:

        node * _current_node;
        std::stack<node *> _way;

    public:

        explicit postfix_iterator(node *tree_root);

    public:

        bool operator==(postfix_iterator const &other) const;

        bool operator!=(postfix_iterator const &other) const;

        postfix_iterator &operator++();

        postfix_iterator operator++(int not_used);

        std::tuple<unsigned int, tkey const&, tvalue const&> operator*() const;

    private:

        node *get_current_node() const;

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

        virtual std::string get_typename() const;


    private:

        fund_alg::logger * get_logger() const override;

        memory * get_outer_allocator() const override;

        virtual size_t get_node_size() const;
    };

    class reading_template_method : protected logger_holder
    {

    private:

        binary_search_tree<tkey, tvalue, tkey_comparer> * _tree;

    public:

        explicit reading_template_method(binary_search_tree<tkey, tvalue, tkey_comparer> *tree);

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

    private:

        fund_alg::logger * get_logger() const override;
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
            std::list<node **> &path_to_subtree_root_exclusive);

    protected:

        virtual void before_remove_inner(
            tkey const &key,
            node *&subtree_root_address,
            std::list<node **> &path_to_subtree_root_exclusive);

        virtual void after_remove_inner(
            tkey const &key,
            node *&subtree_root_address,
            std::list<node **> &path_to_subtree_root_exclusive);

    private:

        template<typename T>
            void swap(T** value, T** another_value)
        {
            T *value_ptr_copy = *value;
            *value = *another_value;
            *another_value = value_ptr_copy;
        }

        void swap_nodes(node **one_node, node **another_node);

    protected:

        virtual void swap_additional_nodes_data(node *one_node, node *another_node);


    private:

        fund_alg::logger * get_logger() const override;

        memory * get_outer_allocator() const override;
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

    memory * get_outer_allocator() const override;

    fund_alg::logger * get_logger() const override;

    virtual size_t get_node_size() const;

private:

    node *copy() const;

    node *copy_inner(node *to_copy) const;

    void move(binary_search_tree<tkey, tvalue, tkey_comparer> &&other);

    void clear();

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
    binary_search_tree<tkey, tvalue, tkey_comparer>::node *tree_root):
    _current_node(tree_root)
{

}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
bool binary_search_tree<tkey, tvalue, tkey_comparer>::prefix_iterator::operator==(
    binary_search_tree<tkey, tvalue, tkey_comparer>::prefix_iterator const &other) const
{
    if (_way == other._way && _current_node == other._current_node)
    {
        return true;
    }

    return false;
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
bool binary_search_tree<tkey, tvalue, tkey_comparer>::prefix_iterator::operator!=(
    prefix_iterator const &other) const
{
    return !(*this == other);
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
typename binary_search_tree<tkey, tvalue, tkey_comparer>::prefix_iterator &binary_search_tree<tkey, tvalue, tkey_comparer>::prefix_iterator::operator++()
{
    if (_current_node == nullptr)
    {
        return *this;
    }

    if (_current_node->left_subtree_address != nullptr)
    {
        _way.push(_current_node);
        _current_node = _current_node->left_subtree_address;

        return *this;
    }
    else if (_current_node->right_subtree_address != nullptr)
    {
        _way.push(_current_node);
        _current_node = _current_node->right_subtree_address;

        return *this;
    }
    else
    {
        while (true)
        {
            if (_way.empty())
            {
                _current_node = nullptr;
                return *this;
            }
            else if (_way.top()->right_subtree_address == _current_node)
            {
                _current_node = _way.top();
                _way.pop();
            }
            else
            {
                if (_way.top()->right_subtree_address != nullptr)
                {
                    _current_node = _way.top()->right_subtree_address;
                    return *this;
                }
                else
                {
                    _current_node = _way.top()->right_subtree_address;
                }
            }

        }
    }
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
typename binary_search_tree<tkey, tvalue, tkey_comparer>::prefix_iterator binary_search_tree<tkey, tvalue, tkey_comparer>::prefix_iterator::operator++(
    int not_used)
{
    typename binary_search_tree<tkey, tvalue, tkey_comparer>::prefix_iterator prev_state = *this;

    ++(*this);

    return prev_state;
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
std::tuple<unsigned int, tkey const&, tvalue const&> binary_search_tree<tkey, tvalue, tkey_comparer>::prefix_iterator::operator*() const
{
    return std::tuple<unsigned int, tkey const&, tvalue const&>(_way.size(), _current_node->key_and_value._key, _current_node->key_and_value._value);
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
    _current_node = tree_root;
    while (_current_node && _current_node->left_subtree_address)
    {
        _way.push(_current_node);
        _current_node = _current_node->left_subtree_address;
    }
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
bool binary_search_tree<tkey, tvalue, tkey_comparer>::infix_iterator::operator==(
    binary_search_tree<tkey, tvalue, tkey_comparer>::infix_iterator const &other) const
{
    if (_way == other._way && _current_node == other._current_node)
    {
        return true;
    }

    return false;
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
bool binary_search_tree<tkey, tvalue, tkey_comparer>::infix_iterator::operator!=(
    binary_search_tree<tkey, tvalue, tkey_comparer>::infix_iterator const &other) const
{
    return !(*this == other);
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
typename binary_search_tree<tkey, tvalue, tkey_comparer>::infix_iterator &binary_search_tree<tkey, tvalue, tkey_comparer>::infix_iterator::operator++()
{
    if (_current_node == nullptr)
    {
        return *this;
    }

    if (_current_node->right_subtree_address != nullptr)
    {
        _way.push(_current_node);
        _current_node = _current_node->right_subtree_address;

        while (_current_node->left_subtree_address != nullptr)
        {
            _way.push(_current_node);
            _current_node = _current_node->left_subtree_address;
        }
    }
    else
    {
        if (!_way.empty())
        {
            if (_way.top()->left_subtree_address == _current_node)
            {
                _current_node = _way.top();
                _way.pop();
            }
            else
            {
                while (!_way.empty() && _way.top()->right_subtree_address == _current_node)
                {
                    _current_node = _way.top();
                    _way.pop();
                }

                if (_way.empty())
                {
                    _current_node = nullptr;
                    return *this;
                }

                _current_node = _way.top();
                _way.pop();
            }
        }
    }

    return *this;
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
typename binary_search_tree<tkey, tvalue, tkey_comparer>::infix_iterator binary_search_tree<tkey, tvalue, tkey_comparer>::infix_iterator::operator++(
    int not_used)
{
    typename binary_search_tree<tkey, tvalue, tkey_comparer>::infix_iterator prev_state = *this;

    ++(*this);

    return prev_state;
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
std::tuple<unsigned int, tkey const&, tvalue const&> binary_search_tree<tkey, tvalue, tkey_comparer>::infix_iterator::operator*() const
{
    return std::tuple<unsigned int, tkey const&, tvalue const&>(_way.size(), _current_node->key_and_value._key, _current_node->key_and_value._value);
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
    _current_node = tree_root;
    while (_current_node != nullptr && _current_node->left_subtree_address != nullptr)
    {
        _way.push(_current_node);
        _current_node = _current_node->left_subtree_address;
    }
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
bool binary_search_tree<tkey, tvalue, tkey_comparer>::postfix_iterator::operator==(
    binary_search_tree<tkey, tvalue, tkey_comparer>::postfix_iterator const &other) const
{
    if (_way == other._way && _current_node == other._current_node)
    {
        return true;
    }

    return false;
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
bool binary_search_tree<tkey, tvalue, tkey_comparer>::postfix_iterator::operator!=(
    binary_search_tree<tkey, tvalue, tkey_comparer>::postfix_iterator const &other) const
{
    return !(*this == other);
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
typename binary_search_tree<tkey, tvalue, tkey_comparer>::postfix_iterator &binary_search_tree<tkey, tvalue, tkey_comparer>::postfix_iterator::operator++()
{
    if (_current_node == nullptr)
    {
        return *this;
    }

    if (_way.empty())
    {
        _current_node = nullptr;
    }
    else
    {
        if (_way.top()->right_subtree_address == _current_node)
        {
            _current_node = _way.top();
            _way.pop();
        }
        else
        {
            if (_way.top()->right_subtree_address != nullptr)
            {
                _current_node = _way.top()->right_subtree_address;

                while (_current_node->left_subtree_address != nullptr || _current_node->right_subtree_address != nullptr)
                {
                    _way.push(_current_node);
                    _current_node = _current_node->left_subtree_address ? _current_node->left_subtree_address : _current_node->right_subtree_address;
                }
            }
            else
            {
                _current_node = _way.top();
                _way.pop();
            }
        }
    }

    return *this;
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
typename binary_search_tree<tkey, tvalue, tkey_comparer>::postfix_iterator binary_search_tree<tkey, tvalue, tkey_comparer>::postfix_iterator::operator++(
    int not_used)
{
    typename binary_search_tree<tkey, tvalue, tkey_comparer>::postfix_iterator prev_state = *this;

    ++(*this);

    return prev_state;
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
std::tuple<unsigned int, tkey const&, tvalue const&> binary_search_tree<tkey, tvalue, tkey_comparer>::postfix_iterator::operator*() const
{
    return std::tuple<unsigned int, tkey const&, tvalue const&>(_way.size(), _current_node->key_and_value._key, _current_node->key_and_value._value);
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
typename binary_search_tree<tkey, tvalue, tkey_comparer>::node *binary_search_tree<tkey, tvalue, tkey_comparer>::postfix_iterator::get_current_node() const {
    return _current_node;
}

// endregion prefix_iterator implementation

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
    auto tree_typename = get_typename();

    this->trace_with_guard("[BST] Initialize node with type {" + tree_typename + "::node}.");

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

    auto insert_node = &subtree_root_address;

    while (*insert_node != nullptr)
    {
        int compare_result = _tree->_comparator(key, (*insert_node)->key_and_value._key);

        if (compare_result == 0)
        {
            std::string message = "Key already exists";
            this->warning_with_guard("[BST] " + message + ".");

            throw std::invalid_argument(message);
        }

        path_to_subtree_root_exclusive.push(insert_node);
        insert_node = &(compare_result > 0 ? (*insert_node)->right_subtree_address : (*insert_node)->left_subtree_address);
    }

    (*insert_node) = reinterpret_cast<node *>(allocate_with_guard(get_node_size()));
    initialize_memory_with_node((*insert_node));
    (*insert_node)->key_and_value._key = key;
    (*insert_node)->key_and_value._value = std::move(value);
    (*insert_node)->left_subtree_address = nullptr;
    (*insert_node)->right_subtree_address = nullptr;

    this->trace_with_guard("[BST] Node with key: {" + to_string(key) + "} inserted.");

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

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
size_t binary_search_tree<tkey, tvalue, tkey_comparer>::insertion_template_method::get_node_size() const
{
    return sizeof(node);
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
memory *binary_search_tree<tkey, tvalue, tkey_comparer>::insertion_template_method::get_outer_allocator() const
{
    return _tree->_allocator;
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
fund_alg::logger *binary_search_tree<tkey, tvalue, tkey_comparer>::insertion_template_method::get_logger() const
{
    return _tree->_logger;
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
        std::string message = "Key not found";
        this->warning_with_guard(message);

        throw std::invalid_argument("[BST] " + message + ".");
    }

    tkey_comparer comparator;

    auto find_node = &subtree_root_address;

    while (*find_node != nullptr)
    {
        int compare_result = comparator(target_key_and_result_value->_key, (*find_node)->key_and_value._key);

        if (compare_result == 0)
        {
            target_key_and_result_value->_value = std::move((*find_node)->key_and_value._value);
            after_read_inner(target_key_and_result_value, subtree_root_address, path_to_subtree_root_exclusive);
            return true;
        }
        else
        {
            path_to_subtree_root_exclusive.push(find_node);
            find_node = &(compare_result > 0 ? (*find_node)->right_subtree_address : (*find_node)->left_subtree_address);
        }
    }
    return false;
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

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
fund_alg::logger *binary_search_tree<tkey, tvalue, tkey_comparer>::reading_template_method::get_logger() const
{
    return _tree->_logger;
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
    std::list<binary_search_tree<tkey, tvalue, tkey_comparer>::node **> path_to_subtree_root_exclusive;

    return std::move(remove_inner(key, tree_root_address, path_to_subtree_root_exclusive));
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
tvalue &&binary_search_tree<tkey, tvalue, tkey_comparer>::removing_template_method::remove_inner(
    tkey const &key,
    binary_search_tree<tkey, tvalue, tkey_comparer>::node *&subtree_root_address,
    std::list<binary_search_tree<tkey, tvalue, tkey_comparer>::node **> &path_to_subtree_root_exclusive)
{
    if (subtree_root_address == nullptr)
    {
        std::string message = "Tree is empty";
        this->warning_with_guard(message);

        throw std::invalid_argument("[BST] " + message + ".");
    }

    auto current_node = &subtree_root_address;
    node ** removed_node = nullptr;

    while (*current_node != nullptr)
    {
        int compare_result = _tree->_comparator(key, (*current_node)->key_and_value._key);

        if (compare_result == 0)
        {
            removed_node = current_node;
            break;
        }
        else
        {
            path_to_subtree_root_exclusive.push_back(current_node);
            current_node = &(compare_result > 0 ? (*current_node)->right_subtree_address : (*current_node)->left_subtree_address);
        }
    }

    if (removed_node == nullptr)
    {
        std::string message = "Key not found";
        this->warning_with_guard(message);

        throw std::invalid_argument("[BST] " + message + ".");
    }

    tvalue && removed_value = std::move((*removed_node)->key_and_value._value);

    auto removal_completed = false;

    if ((*removed_node)->left_subtree_address != nullptr && (*removed_node)->right_subtree_address != nullptr)
    {
        auto successor = (*removed_node)->right_subtree_address;
        auto right_subtree_root = &(*removed_node)->right_subtree_address;

        if (successor->left_subtree_address == nullptr)
        {
            successor->left_subtree_address = (*removed_node)->left_subtree_address;
            (*removed_node)->~node();
            deallocate_with_guard(*removed_node);
            *removed_node = successor;
            removal_completed = true;
        }
        else
        {
            path_to_subtree_root_exclusive.push_back(removed_node);
            auto removed_node_list_id = path_to_subtree_root_exclusive.size() - 1;
            path_to_subtree_root_exclusive.push_back(&(*removed_node)->right_subtree_address);

            while (successor->left_subtree_address != nullptr)
            {
                path_to_subtree_root_exclusive.push_back(&(successor->left_subtree_address));
                successor = successor->left_subtree_address;
            }

            auto it1 = path_to_subtree_root_exclusive.begin();
            std::advance(it1, removed_node_list_id);
            auto it2 = path_to_subtree_root_exclusive.rbegin();
            swap_nodes(*it1, *it2);
            std::advance(it1, 1);
            *it1 = right_subtree_root;

            removed_node = *path_to_subtree_root_exclusive.rbegin();
            path_to_subtree_root_exclusive.pop_back();
        }
    }

    if (!removal_completed) {
        if ((*removed_node)->left_subtree_address == nullptr && (*removed_node)->right_subtree_address == nullptr) {
            (*removed_node)->~node();
            deallocate_with_guard((*removed_node));
            (*removed_node) = nullptr;
        } else {
            auto tmp = (*removed_node)->left_subtree_address != nullptr ? (*removed_node)->left_subtree_address
                                                                        : (*removed_node)->right_subtree_address;
            (*removed_node)->~node();
            deallocate_with_guard((*removed_node));
            (*removed_node) = tmp;
        }
    }

    this->trace_with_guard("[BST] Node with key: {" + to_string(key) + "} has been deleted.");

    after_remove_inner(key, subtree_root_address, path_to_subtree_root_exclusive);

    return std::move(removed_value);
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::removing_template_method::before_remove_inner(
    tkey const &key,
    binary_search_tree<tkey, tvalue, tkey_comparer>::node *&subtree_root_address,
    std::list<binary_search_tree<tkey, tvalue, tkey_comparer>::node **> &path_to_subtree_root_exclusive)
{

}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::removing_template_method::after_remove_inner(
    tkey const &key,
    binary_search_tree<tkey, tvalue, tkey_comparer>::node *&subtree_root_address,
    std::list<binary_search_tree<tkey, tvalue, tkey_comparer>::node **> &path_to_subtree_root_exclusive)
{

}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
memory *binary_search_tree<tkey, tvalue, tkey_comparer>::removing_template_method::get_outer_allocator() const
{
    return _tree->_allocator;
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
fund_alg::logger *binary_search_tree<tkey, tvalue, tkey_comparer>::removing_template_method::get_logger() const
{
    return _tree->_logger;
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::removing_template_method::swap_additional_nodes_data(
        binary_search_tree::node *one_node, binary_search_tree::node *another_node)
{

}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::removing_template_method::swap_nodes(
        binary_search_tree::node **one_node, binary_search_tree::node **another_node)
{
    swap(one_node, another_node);
    swap(&(*one_node)->left_subtree_address, &(*another_node)->left_subtree_address);
    swap(&(*one_node)->right_subtree_address, &(*another_node)->right_subtree_address);
    swap_additional_nodes_data(*one_node, *another_node);
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
binary_search_tree<tkey, tvalue, tkey_comparer>::reading_template_method::reading_template_method(
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
void binary_search_tree<tkey, tvalue, tkey_comparer>::move(binary_search_tree<tkey, tvalue, tkey_comparer> &&other)
{
    _root = other._root;
    other._root = nullptr;

    _allocator = other._allocator;
    other._allocator = nullptr;

    _logger = other._logger;
    other._logger = nullptr;

    _insertion = other._insertion;
    other._insertion = nullptr;

    _reading = other._reading;
    other._reading = nullptr;

    _removing = other._removing;
    other._removing = nullptr;
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
typename binary_search_tree<tkey, tvalue, tkey_comparer>::node *binary_search_tree<tkey, tvalue, tkey_comparer>::copy() const
{
    return copy_inner(_root);
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
typename binary_search_tree<tkey, tvalue, tkey_comparer>::node *binary_search_tree<tkey, tvalue, tkey_comparer>::copy_inner(typename binary_search_tree<tkey, tvalue, tkey_comparer>::node *to_copy) const
{
    if (to_copy == nullptr)
    {
        return nullptr;
    }

    auto *node_copy = reinterpret_cast<binary_search_tree<tkey, tvalue, tkey_comparer>::node *>(allocate_with_guard(get_node_size()));

    new (node_copy) binary_search_tree<tkey, tvalue, tkey_comparer>::node();
    node_copy->key_and_value._key = to_copy->key_and_value._key;
    node_copy->key_and_value._value = to_copy->key_and_value._value;
    node_copy->left_subtree_address = copy_inner(to_copy->left_subtree_address);
    node_copy->right_subtree_address = copy_inner(to_copy->right_subtree_address);

    return node_copy;
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void binary_search_tree<tkey, tvalue, tkey_comparer>::clear() {
    auto it_end = end_postfix();
    for (auto it = begin_postfix(); it != it_end; ++it)
    {
        it.get_current_node()->~node();
        deallocate_with_guard(it.get_current_node());
    }
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
    _insertion(new insertion_template_method(this)),
    _reading(new reading_template_method(this)),
    _removing(new removing_template_method(this)),
    _allocator(allocator),
    _logger(logger),
    _root(nullptr)
{
    this->trace_with_guard("The tree has been created.");
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
binary_search_tree<tkey, tvalue, tkey_comparer>::binary_search_tree(
    const binary_search_tree &other)
    : binary_search_tree<tkey, tvalue, tkey_comparer>(other._allocator, other._logger)
{
    _root = other.copy();

    this->trace_with_guard("The tree has been copy.");
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
binary_search_tree<tkey, tvalue, tkey_comparer>::binary_search_tree(
    binary_search_tree &&other) noexcept
{
    move(std::move(other));

    this->trace_with_guard("The tree has been moved.");
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

    clear();
    _root = other.copy();

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

    clear();
    delete _insertion;
    delete _reading;
    delete _removing;
    move(std::move(other));

    return *this;
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
binary_search_tree<tkey, tvalue, tkey_comparer>::~binary_search_tree()
{
    clear();

    delete _insertion;
    delete _reading;
    delete _removing;

    this->trace_with_guard("The tree has been deleted.");
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

// region logger_holder, memory_holder and other contract implementation

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
size_t binary_search_tree<tkey, tvalue, tkey_comparer>::get_node_size() const
{
    return sizeof(node);
}

template<
     typename tkey,
     typename tvalue,
     typename tkey_comparer>
std::string binary_search_tree<tkey, tvalue, tkey_comparer>::insertion_template_method::get_typename() const
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
    return prefix_iterator(_root);
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
typename binary_search_tree<tkey, tvalue, tkey_comparer>::prefix_iterator binary_search_tree<tkey, tvalue, tkey_comparer>::end_prefix() const noexcept
{
    return prefix_iterator(nullptr);
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
typename binary_search_tree<tkey, tvalue, tkey_comparer>::infix_iterator binary_search_tree<tkey, tvalue, tkey_comparer>::begin_infix() const noexcept
{
    return infix_iterator(_root);
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
typename binary_search_tree<tkey, tvalue, tkey_comparer>::infix_iterator binary_search_tree<tkey, tvalue, tkey_comparer>::end_infix() const noexcept
{
    return infix_iterator(nullptr);
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
typename binary_search_tree<tkey, tvalue, tkey_comparer>::postfix_iterator binary_search_tree<tkey, tvalue, tkey_comparer>::begin_postfix() const noexcept
{
    return postfix_iterator(_root);
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
typename binary_search_tree<tkey, tvalue, tkey_comparer>::postfix_iterator binary_search_tree<tkey, tvalue, tkey_comparer>::end_postfix() const noexcept
{
    return postfix_iterator(nullptr);
}

// endregion iterators requesting implementation

#endif //BINARY_SEARCH_TREE_H
