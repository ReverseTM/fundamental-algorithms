#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H

#include "binary_search_tree.h"

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
class splay_tree final : public binary_search_tree<tkey, tvalue, tkey_comparer>
{

private:

    class splay_tree_insertion_template_method final : public binary_search_tree<tkey, tvalue, tkey_comparer>::insertion_template_method
    {

    public:

        explicit splay_tree_insertion_template_method(splay_tree<tkey, tvalue, tkey_comparer> * tree);

    protected:

        void after_insert_inner(
                tkey const &key,
                typename binary_search_tree<tkey, tvalue, tkey_comparer>::node *&subtree_root_address,
                std::stack<typename binary_search_tree<tkey, tvalue, tkey_comparer>::node **> &path_to_subtree_root_exclusive) override;
    };

    class splay_tree_reading_template_method final : public binary_search_tree<tkey, tvalue, tkey_comparer>::reading_template_method
    {

    public:

        explicit splay_tree_reading_template_method(splay_tree<tkey, tvalue, tkey_comparer> * tree);

    protected:

        void after_read_inner(
                typename associative_container<tkey, tvalue>::key_value_pair * target_key_and_result_value,
                typename binary_search_tree<tkey, tvalue, tkey_comparer>::node *&subtree_root_address,
                std::stack<typename binary_search_tree<tkey, tvalue, tkey_comparer>::node **> &path_to_subtree_root_exclusive) override;

    };

    class splay_tree_removing_template_method final : public binary_search_tree<tkey, tvalue, tkey_comparer>::removing_template_method
    {

    public:

        explicit splay_tree_removing_template_method(splay_tree<tkey, tvalue, tkey_comparer> * tree);

    protected:

        tvalue remove_inner(
                tkey const &key,
                typename binary_search_tree<tkey, tvalue, tkey_comparer>::node *& subtree_root_address,
                std::stack<typename binary_search_tree<tkey, tvalue, tkey_comparer>::node **> &path_to_subtree_root_exclusive
                ) override;
    };

private:

    void splay(
            typename binary_search_tree<tkey, tvalue, tkey_comparer>::node *&subtree_root_address,
            std::stack<typename binary_search_tree<tkey, tvalue, tkey_comparer>::node **> &path_to_subtree_root_exclusive) const;

    typename binary_search_tree<tkey, tvalue, tkey_comparer>::node * merge(
            typename binary_search_tree<tkey, tvalue, tkey_comparer>::node *&left_subtree,
            typename binary_search_tree<tkey, tvalue, tkey_comparer>::node *&right_subtree);

public:

    explicit splay_tree(memory *allocator = nullptr, fund_alg::logger *logger = nullptr);

    ~splay_tree() final = default;

    splay_tree(
         splay_tree const &other);

    splay_tree(
         splay_tree &&other) noexcept;

    splay_tree &operator=(
         splay_tree const &other);

    splay_tree &operator=(
         splay_tree &&other) noexcept;

};

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
void splay_tree<tkey, tvalue, tkey_comparer>::splay(
        typename binary_search_tree<tkey, tvalue, tkey_comparer>::node *&subtree_root_address,
        std::stack<typename binary_search_tree<tkey, tvalue, tkey_comparer>::node **> &path_to_subtree_root_exclusive) const
{
    typename binary_search_tree<tkey, tvalue, tkey_comparer>::node * current_node = subtree_root_address;
    typename binary_search_tree<tkey, tvalue, tkey_comparer>::node ** parent = nullptr;
    typename binary_search_tree<tkey, tvalue, tkey_comparer>::node ** grand_parent = nullptr;

    while (!path_to_subtree_root_exclusive.empty())
    {
        if (path_to_subtree_root_exclusive.size() == 1)
        {
            parent = path_to_subtree_root_exclusive.top();

            if ((*parent)->left_subtree_address == current_node)
            {
                this->right_rotation(*parent);
            }
            else
            {
                this->left_rotation(*parent);
            }

            path_to_subtree_root_exclusive.pop();
        }
        else
        {
            parent = path_to_subtree_root_exclusive.top();
            path_to_subtree_root_exclusive.pop();

            grand_parent = path_to_subtree_root_exclusive.top();
            path_to_subtree_root_exclusive.pop();

            if ((*parent)->left_subtree_address == current_node && (*grand_parent)->left_subtree_address == *parent)
            {
                this->right_rotation(*grand_parent);
                this->right_rotation(*grand_parent);
                current_node = *grand_parent;
            }
            else if ((*parent)->right_subtree_address == current_node && (*grand_parent)->right_subtree_address == *parent)
            {
                this->left_rotation(*grand_parent);
                this->left_rotation(*grand_parent);
                current_node = *grand_parent;
            }
            else if ((*parent)->right_subtree_address == current_node && (*grand_parent)->left_subtree_address == *parent)
            {
                this->left_rotation(*parent);
                this->right_rotation(*grand_parent);
                current_node = *grand_parent;
            }
            else
            {
                this->right_rotation(*parent);
                this->left_rotation(*grand_parent);
                current_node = *grand_parent;
            }
        }
    }
}

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
typename binary_search_tree<tkey, tvalue, tkey_comparer>::node * splay_tree<tkey, tvalue, tkey_comparer>::merge(
        typename binary_search_tree<tkey, tvalue, tkey_comparer>::node *&left_subtree,
        typename binary_search_tree<tkey, tvalue, tkey_comparer>::node *&right_subtree)
{
    if (left_subtree == nullptr && right_subtree == nullptr)
    {
        return nullptr;
    }

    if (left_subtree == nullptr && right_subtree != nullptr)
    {
        return right_subtree;
    }
    else if (left_subtree != nullptr && right_subtree == nullptr)
    {
        return left_subtree;
    }
    else
    {
        std::stack<typename binary_search_tree<tkey, tvalue, tkey_comparer>::node **> path_to_subtree_root_exclusive;

        typename binary_search_tree<tkey, tvalue, tkey_comparer>::node * successor = left_subtree;
        typename binary_search_tree<tkey, tvalue, tkey_comparer>::node ** previous_node_address = &left_subtree;

        while (successor->right_subtree_address != nullptr)
        {
            path_to_subtree_root_exclusive.push(previous_node_address);
            previous_node_address = &(successor->right_subtree_address);
            successor = successor->right_subtree_address;
        }

        splay(successor, path_to_subtree_root_exclusive);

        left_subtree->right_subtree_address = right_subtree;

        return left_subtree;
    }
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void splay_tree<tkey, tvalue, tkey_comparer>::splay_tree_insertion_template_method::after_insert_inner(
    const tkey &key,
    typename binary_search_tree<tkey, tvalue, tkey_comparer>::node *&subtree_root_address,
    std::stack<typename binary_search_tree<tkey, tvalue, tkey_comparer>::node **> &path_to_subtree_root_exclusive)
{
    reinterpret_cast<splay_tree<tkey, tvalue, tkey_comparer> *>(this->_tree)->splay(subtree_root_address, path_to_subtree_root_exclusive);

    this->trace_with_guard("[SPLAY TREE] Node with key: {" + to_string(key) + "} inserted.");
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void splay_tree<tkey, tvalue, tkey_comparer>::splay_tree_reading_template_method::after_read_inner(
    typename associative_container<tkey, tvalue>::key_value_pair * target_key_and_result_value,
    typename binary_search_tree<tkey, tvalue, tkey_comparer>::node *&subtree_root_address,
    std::stack<typename binary_search_tree<tkey, tvalue, tkey_comparer>::node **> &path_to_subtree_root_exclusive)
{
    reinterpret_cast<splay_tree<tkey, tvalue, tkey_comparer> *>(this->_tree)->splay(subtree_root_address, path_to_subtree_root_exclusive);
}

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
tvalue splay_tree<tkey, tvalue, tkey_comparer>::splay_tree_removing_template_method::remove_inner(
        const tkey &key,
        typename binary_search_tree<tkey, tvalue, tkey_comparer>::node *&subtree_root_address,
        std::stack<typename binary_search_tree<tkey, tvalue, tkey_comparer>::node **> &path_to_subtree_root_exclusive)
{
    if (subtree_root_address == nullptr)
    {
        std::string message = "Tree is empty";
        this->warning_with_guard(message);

        throw std::invalid_argument("[SPLAY TREE] " + message + ".");
    }

    typename binary_search_tree<tkey, tvalue, tkey_comparer>::node ** current_node = &subtree_root_address;

    tkey_comparer comparator;

    while (*current_node != nullptr)
    {
        int compare_result = comparator(key, (*current_node)->key_and_value._key);

        if (compare_result == 0)
        {
            break;
        }
        else
        {
            path_to_subtree_root_exclusive.push(current_node);
            current_node = &(compare_result > 0 ? (*current_node)->right_subtree_address : (*current_node)->left_subtree_address);
        }
    }

    if ((*current_node) == nullptr)
    {
        std::string message = "Key not found";
        this->warning_with_guard(message);

        throw std::invalid_argument("[SPLAY TREE] " + message + ".");
    }

    tvalue removed_value = std::move((*current_node)->key_and_value._value);

    reinterpret_cast<splay_tree<tkey, tvalue, tkey_comparer> *>(this->_tree)->splay(*current_node, path_to_subtree_root_exclusive);

    typename binary_search_tree<tkey, tvalue, tkey_comparer>::node * left_subtree = subtree_root_address->left_subtree_address;
    typename binary_search_tree<tkey, tvalue, tkey_comparer>::node * right_subtree = subtree_root_address->right_subtree_address;

     subtree_root_address->~node();

    reinterpret_cast<splay_tree<tkey, tvalue, tkey_comparer> *>(this->_tree)->deallocate_with_guard(subtree_root_address);

    this->trace_with_guard("[SPLAY TREE] Node with key: {" + to_string(key) + "} has been deleted.");

    reinterpret_cast<splay_tree<tkey, tvalue, tkey_comparer> *>(this->_tree)->_root = reinterpret_cast<splay_tree<tkey, tvalue, tkey_comparer> *>(this->_tree)->merge(left_subtree, right_subtree);

    return removed_value;
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
splay_tree<tkey, tvalue, tkey_comparer>::splay_tree_insertion_template_method::splay_tree_insertion_template_method(
    splay_tree<tkey, tvalue, tkey_comparer> *tree):
    binary_search_tree<tkey, tvalue, tkey_comparer>::insertion_template_method(tree)
{

}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
splay_tree<tkey, tvalue, tkey_comparer>::splay_tree_reading_template_method::splay_tree_reading_template_method(
    splay_tree<tkey, tvalue, tkey_comparer> *tree):
    binary_search_tree<tkey, tvalue, tkey_comparer>::reading_template_method(tree)
{

}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
splay_tree<tkey, tvalue, tkey_comparer>::splay_tree_removing_template_method::splay_tree_removing_template_method(
    splay_tree<tkey, tvalue, tkey_comparer> *tree):
    binary_search_tree<tkey, tvalue, tkey_comparer>::removing_template_method(tree)
{

}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
splay_tree<tkey, tvalue, tkey_comparer>::splay_tree(memory *allocator, fund_alg::logger *logger):
        binary_search_tree<tkey, tvalue, tkey_comparer>(
        new splay_tree_insertion_template_method(this),
        new splay_tree_reading_template_method(this),
        new splay_tree_removing_template_method(this),
        allocator,
        logger)
{
    this->trace_with_guard("[SPLAY TREE] The tree has been created.");
}

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
splay_tree<tkey, tvalue, tkey_comparer>::splay_tree(splay_tree<tkey, tvalue, tkey_comparer> const &other)
        : splay_tree<tkey, tvalue, tkey_comparer>(other.get_outer_allocator(), other.get_logger())
{
    this->_root = other.copy();

    this->trace_with_guard("The tree has been copy.");
}

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
splay_tree<tkey, tvalue, tkey_comparer>::splay_tree(splay_tree<tkey, tvalue, tkey_comparer> &&other) noexcept
        : binary_search_tree<tkey, tvalue, tkey_comparer>(std::move(other))
{

}

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
splay_tree<tkey, tvalue, tkey_comparer> &splay_tree<tkey, tvalue, tkey_comparer>::operator=(splay_tree<tkey, tvalue, tkey_comparer> const &other)
{
    static_cast<binary_search_tree<tkey, tvalue, tkey_comparer> &>(*this) = other;

    return *this;
}

template<
        typename tkey,
        typename tvalue,
        typename tkey_comparer>
splay_tree<tkey, tvalue, tkey_comparer> &splay_tree<tkey, tvalue, tkey_comparer>::operator=(splay_tree<tkey, tvalue, tkey_comparer> &&other) noexcept
{
    static_cast<binary_search_tree<tkey, tvalue, tkey_comparer> &>(*this) = std::move(other);

    return *this;
}

#endif //SPLAY_TREE_H
