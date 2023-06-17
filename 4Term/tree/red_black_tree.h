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

private:

    class rb_tree_insertion_template_method final : public binary_search_tree<tkey, tvalue, tkey_comparer>::insertion_template_method
    {

    protected:

        void after_insert_inner(
                tkey const &key,
                typename binary_search_tree<tkey, tvalue, tkey_comparer>::node *&subtree_root_address,
                std::stack<typename binary_search_tree<tkey, tvalue, tkey_comparer>::node **> &path_to_subtree_root_exclusive) override;

        void call_node_constructor(typename binary_search_tree<tkey, tvalue, tkey_comparer>::node * node_address) const override;

        void initialize_additional_data(binary_search_tree<tkey, tvalue, tkey_comparer>::node * node_address) const override;

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

    node_color get_color(rb_node * subtree_root) const noexcept;

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
size_t rb_tree<tkey, tvalue, tkey_comparer>::rb_tree_insertion_template_method::get_node_size() const
{
    return sizeof(rb_node);
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void rb_tree<tkey, tvalue, tkey_comparer>::rb_tree_insertion_template_method::call_node_constructor(
        binary_search_tree<tkey, tvalue, tkey_comparer>::node *node_address) const
{
    new (node_address) rb_node;
}

template<
    typename tkey,
    typename tvalue,
    typename tkey_comparer>
void rb_tree<tkey, tvalue, tkey_comparer>::rb_tree_insertion_template_method::initialize_additional_data(
        binary_search_tree<tkey, tvalue, tkey_comparer>::node *node_address) const
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
