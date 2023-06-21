#ifndef RED_BLACK_TREE_H
#define RED_BLACK_TREE_H

#include "binary_search_tree.h"

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
class rb_tree final : public binary_search_tree<tkey, tvalue, tkey_comparer>
{

private:

    enum class node_color
    {
        BLACK,
        RED
    };

    struct rb_node final : public binary_search_tree<tkey, tvalue, tkey_comparer>::node
    {
        node_color color;
    };

public:

    void prefix_traverse()
    {
        prefix_traverse_inner(reinterpret_cast<typename rb_tree<tkey, tvalue, tkey_comparer>::rb_node *>(this->get_root()), 0);
    }

private:

    rb_node * get_root()
    {
        return reinterpret_cast<rb_node *>(this->_root);
    }

    void prefix_traverse_inner(typename rb_tree<tkey, tvalue, tkey_comparer>::rb_node *rb_node, unsigned int depth)
    {
        if (rb_node == nullptr)
        {
            return;
        }

        for (auto i = 0; i < depth; i++)
        {
            std::cout << "  ";
        }
        std::cout << "Key == " << rb_node->key_and_value._key << ", color == " << (rb_node->color == node_color::RED ? "red" : "black") << std::endl;

        prefix_traverse_inner(reinterpret_cast<typename rb_tree<tkey, tvalue, tkey_comparer>::rb_node *>(rb_node->left_subtree_address), depth + 1);
        prefix_traverse_inner(reinterpret_cast<typename rb_tree<tkey, tvalue, tkey_comparer>::rb_node *>(rb_node->right_subtree_address), depth + 1);
    }

private:

    class rb_tree_insertion_template_method final : public binary_search_tree<tkey, tvalue, tkey_comparer>::insertion_template_method
    {

    protected:

        void after_insert_inner(
                tkey const &key,
                typename binary_search_tree<tkey, tvalue, tkey_comparer>::node *&subtree_root_address,
                std::stack<typename binary_search_tree<tkey, tvalue, tkey_comparer>::node **> &path_to_subtree_root_exclusive) override;

        void call_node_constructor(typename binary_search_tree<tkey, tvalue, tkey_comparer>::node * node_address) const override;

        void initialize_additional_data(typename binary_search_tree<tkey, tvalue, tkey_comparer>::node * node_address) const override;

        size_t get_node_size() const override;

    public:

        explicit rb_tree_insertion_template_method(rb_tree<tkey, tvalue, tkey_comparer> * tree);

    };

    class rb_tree_removing_template_method final : public binary_search_tree<tkey, tvalue, tkey_comparer>::removing_template_method
    {

    protected:

        void after_remove_inner(
                tkey const &key,
                typename binary_search_tree<tkey, tvalue, tkey_comparer>::node *&subtree_root_address,
                std::stack<typename binary_search_tree<tkey, tvalue, tkey_comparer>::node **> &path_to_subtree_root_exclusive) override;

    public:

        explicit rb_tree_removing_template_method(rb_tree<tkey, tvalue, tkey_comparer> * tree);

    };

private:

    node_color get_color(typename binary_search_tree<tkey, tvalue, tkey_comparer>::node * subtree_root) const noexcept;

public:

    explicit rb_tree(memory * allocator = nullptr, fund_alg::logger * logger = nullptr);

    ~rb_tree() final = default;

    rb_tree(
        rb_tree const &other);

    rb_tree(
        rb_tree &&other) noexcept;

    rb_tree &operator=(
        rb_tree const &other);

     rb_tree &operator=(
        rb_tree &&other) noexcept;

};

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
typename rb_tree<tkey, tvalue, tkey_comparer>::node_color rb_tree<tkey, tvalue, tkey_comparer>::get_color(typename binary_search_tree<tkey, tvalue, tkey_comparer>::node * subtree_root) const noexcept
{
    return reinterpret_cast<rb_node *>(subtree_root)->color;
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
size_t rb_tree<tkey, tvalue, tkey_comparer>::rb_tree_insertion_template_method::get_node_size() const
{
    return sizeof(rb_node);
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void rb_tree<tkey, tvalue, tkey_comparer>::rb_tree_insertion_template_method::call_node_constructor(
        typename binary_search_tree<tkey, tvalue, tkey_comparer>::node *node_address) const
{
    new (node_address) rb_node;
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void rb_tree<tkey, tvalue, tkey_comparer>::rb_tree_insertion_template_method::initialize_additional_data(
        typename binary_search_tree<tkey, tvalue, tkey_comparer>::node *node_address) const
{
    reinterpret_cast<rb_tree<tkey, tvalue, tkey_comparer>::rb_node *>(node_address)->color = rb_tree<tkey, tvalue, tkey_comparer>::node_color::RED;
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void rb_tree<tkey, tvalue, tkey_comparer>::rb_tree_insertion_template_method::after_insert_inner(
        const tkey &key,
        typename binary_search_tree<tkey, tvalue, tkey_comparer>::node *&subtree_root_address,
        std::stack<typename binary_search_tree<tkey, tvalue, tkey_comparer>::node **> &path_to_subtree_root_exclusive)
{
    if (path_to_subtree_root_exclusive.empty())
    {
        reinterpret_cast<rb_node *>(subtree_root_address)->color = rb_tree<tkey, tvalue, tkey_comparer>::node_color::BLACK;

        return;
    }
    else
    {
        typename binary_search_tree<tkey, tvalue, tkey_comparer>::node **parent = nullptr;
        typename binary_search_tree<tkey, tvalue, tkey_comparer>::node **grand_parent = nullptr;
        typename binary_search_tree<tkey, tvalue, tkey_comparer>::node **uncle = nullptr;

        parent = path_to_subtree_root_exclusive.top();
        path_to_subtree_root_exclusive.pop();

        if (!path_to_subtree_root_exclusive.empty())
        {
            grand_parent = path_to_subtree_root_exclusive.top();
            path_to_subtree_root_exclusive.pop();

            //CASE A: PARENT OF X IS LEFT CHILD OF GRANDPA

            if (*parent == (*grand_parent)->left_subtree_address)
            {
                uncle = &((*grand_parent)->right_subtree_address);

                //CASE 1: UNCLE IS RED
                if (*uncle != nullptr &&
                reinterpret_cast<rb_tree<tkey, tvalue, tkey_comparer> *>(this->_tree)->get_color(*uncle) == node_color::RED)
                {
                    reinterpret_cast<rb_node *>(*grand_parent)->color = node_color::RED;
                    reinterpret_cast<rb_node *>(*parent)->color = node_color::BLACK;
                    reinterpret_cast<rb_node *>(*uncle)->color = node_color::BLACK;
                    after_insert_inner(key, *grand_parent, path_to_subtree_root_exclusive);
                }
                else //UNCLE IS BLACK
                {
                    //CASE 2: X IS RIGHT CHILD OF PARENT
                    if (subtree_root_address == (*parent)->right_subtree_address)
                    {
                        reinterpret_cast<rb_tree<tkey, tvalue, tkey_comparer> *>(this->_tree)->left_rotation(*parent);
                    }

                    //CASE 3: X IS LEFT CHILD OF PARENT
                    reinterpret_cast<rb_tree<tkey, tvalue, tkey_comparer> *>(this->_tree)->right_rotation(*grand_parent);
                    parent = grand_parent;
                    grand_parent = &((*parent)->right_subtree_address);
                    reinterpret_cast<rb_node *>(*parent)->color = node_color::BLACK;
                    reinterpret_cast<rb_node *>(*grand_parent)->color = node_color::RED;

                    //??
                    after_insert_inner(key, *parent, path_to_subtree_root_exclusive);
                }
            }

            //CASE B: PARENT OF X IS RIGHT CHILD OF GRANDPA

            else
            {
                uncle = &((*grand_parent)->left_subtree_address);

                //CASE 1: UNCLE IS RED
                if (*uncle != nullptr && reinterpret_cast<rb_tree<tkey, tvalue, tkey_comparer> *>(this->_tree)->get_color(*uncle) ==node_color::RED)
                {
                    reinterpret_cast<rb_node *>(*grand_parent)->color = node_color::RED;
                    reinterpret_cast<rb_node *>(*parent)->color = node_color::BLACK;
                    reinterpret_cast<rb_node *>(*uncle)->color = node_color::BLACK;
                    after_insert_inner(key, *grand_parent, path_to_subtree_root_exclusive);
                }
                else //UNCLE IS BLACK
                {
                    //CASE 2: X IS LEFT CHILD OF PARENT
                    if (subtree_root_address == (*parent)->left_subtree_address)
                    {
                        reinterpret_cast<rb_tree<tkey, tvalue, tkey_comparer> *>(this->_tree)->right_rotation(*parent);
                    }

                    //CASE 3: X IS RIGHT CHILD OF PARENT
                    reinterpret_cast<rb_tree<tkey, tvalue, tkey_comparer> *>(this->_tree)->left_rotation(*grand_parent);
                    parent = grand_parent;
                    grand_parent = &((*parent)->left_subtree_address);
                    reinterpret_cast<rb_node *>(*parent)->color = node_color::BLACK;
                    reinterpret_cast<rb_node *>(*grand_parent)->color = node_color::RED;

                    //??
                    after_insert_inner(key, *parent, path_to_subtree_root_exclusive);
                }
            }
        }
    }
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void rb_tree<tkey, tvalue, tkey_comparer>::rb_tree_removing_template_method::after_remove_inner(
        const tkey &key,
        typename binary_search_tree<tkey, tvalue, tkey_comparer>::node *&subtree_root_address,
        std::stack<typename binary_search_tree<tkey, tvalue, tkey_comparer>::node **> &path_to_subtree_root_exclusive)
{

}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
rb_tree<tkey, tvalue, tkey_comparer>::rb_tree_insertion_template_method::rb_tree_insertion_template_method(
        rb_tree<tkey, tvalue, tkey_comparer> *tree)
        : binary_search_tree<tkey, tvalue, tkey_comparer>::insertion_template_method(tree)
{

}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
rb_tree<tkey, tvalue, tkey_comparer>::rb_tree_removing_template_method::rb_tree_removing_template_method(
        rb_tree<tkey, tvalue, tkey_comparer> *tree)
        : binary_search_tree<tkey, tvalue, tkey_comparer>::removing_template_method(tree)
{

}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
rb_tree<tkey, tvalue, tkey_comparer>::rb_tree(memory * allocator, fund_alg::logger * logger):
        binary_search_tree<tkey, tvalue, tkey_comparer>(
            new rb_tree_insertion_template_method(this),
            new typename binary_search_tree<tkey, tvalue, tkey_comparer>::reading_template_method(this),
            new rb_tree_removing_template_method(this),
            allocator,
            logger)
{
    this->trace_with_guard("[RED BLACK TREE] The tree has been created.");
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
rb_tree<tkey, tvalue, tkey_comparer>::rb_tree(rb_tree<tkey, tvalue, tkey_comparer> const &other)
{
    
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
rb_tree<tkey, tvalue, tkey_comparer>::rb_tree(rb_tree<tkey, tvalue, tkey_comparer> &&other) noexcept
{

}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
rb_tree<tkey, tvalue, tkey_comparer> &rb_tree<tkey, tvalue, tkey_comparer>::operator=(rb_tree<tkey, tvalue, tkey_comparer> const &other)
{

}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
rb_tree<tkey, tvalue, tkey_comparer> &rb_tree<tkey, tvalue, tkey_comparer>::operator=(rb_tree<tkey, tvalue, tkey_comparer> &&other) noexcept
{

}

#endif //RED_BLACK_TREE_H
