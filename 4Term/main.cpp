#include <iostream>
#include "logger/logger_implementation.h"
#include "logger/builder_implementation.h"
#include "memory_allocators/global_heap_allocator.h"
#include "memory_allocators/sorted_list_allocator.h"
#include "memory_allocators/border_descriptors_allocator.h"
#include "memory_allocators/buddy_allocator.h"
#include "tree/binary_search_tree.h"
#include "tree/splay_tree.h"
#include "tree/avl_tree.h"
#include "tree/red_black_tree.h"
#include <list>

/*
 * постфиксный (лево право корень)
 * инфиксный (лево корень право)
 * префиксный(корень лево право)
 */

class key_comparer
{
public:

    int operator()(int first, int second)
    {
        return first - second;
    }

    int operator()(std::string first, std::string second)
    {
        if (first > second)
            return 1;
        else if (first < second)
            return -1;
        else
            return 0;
    }
};

void testing_allocator()
{
    std::unique_ptr<builder> logger_builder = std::make_unique<builder_implementation>();

    auto logger = logger_builder->add_stream("logs.txt", fund_alg::logger::severity::trace)->build();

    std::shared_ptr<memory> allocator1 = std::make_shared<global_heap_allocator>(logger.get());
    std::shared_ptr<memory> allocator2 = std::make_shared<sorted_list_allocator>(1000000, memory::allocation_mode::first_match, logger.get(), allocator1.get());
    std::shared_ptr<memory> allocator3 = std::make_shared<border_descriptors_allocator>(700000, memory::allocation_mode::first_match, logger.get(), allocator2.get());
    std::shared_ptr<memory> allocator4 = std::make_shared<buddy_system_allocator>(15, memory::allocation_mode::first_match, logger.get(), allocator3.get());

    std::list<void*> allocated_blocks;

    srand((unsigned)time(nullptr));

    for (size_t i = 0; i < 20000; ++i)
    {
        void * ptr;

        switch (rand() % 2)
        {
            case 0:
                try
                {
                    ptr = reinterpret_cast<void *>(allocator4->allocate(rand() % 81 + 20)); // разность макс и мин с включенными границами + минимальное
                    allocated_blocks.push_back(ptr);
                }
                catch (std::exception const &ex)
                {
                    std::cout << ex.what() << std::endl;
                }
                break;
            case 1:

                if (allocated_blocks.empty())
                {
                    break;
                }

                try
                {
                    auto iter = allocated_blocks.begin();
                    std::advance(iter, rand() % allocated_blocks.size());
                    allocator4->deallocate(*iter);
                    allocated_blocks.erase(iter);
                }
                catch (std::exception const &ex)
                {
                    std::cout << ex.what() << std::endl;
                }
                break;
        }

        std::cout << "iter # " << i + 1 << " finish" << std::endl;
    }

    while (!allocated_blocks.empty())
    {
        try
        {
            auto iter = allocated_blocks.begin();
            allocator4->deallocate(*iter);
            allocated_blocks.erase(iter);
        }
        catch (std::exception const &ex)
        {
            std::cout << ex.what() << std::endl;
        }
    }

}

void test_trees()
{
    builder * builder1 = new builder_implementation();
    auto log = builder1
            ->add_stream("file1.txt", fund_alg::logger::severity::trace)
            ->add_stream("file2.txt", fund_alg::logger::severity::debug)
            ->build();

    memory *allocator = new sorted_list_allocator(5000000, memory::allocation_mode::first_match, log.get(), nullptr);

    auto * tree = new avl_tree<int, std::string, key_comparer>(allocator, log.get());

    srand((unsigned)time(nullptr));

    for (auto i = 1; i <= 500000; i++)
    {
        if (i % 1000 == 0)
        {
            std::cout << "Iteration " << i << "..." << std::endl;
        }

        associative_container<int, std::string>::key_value_pair ваще_пахую;

        switch (rand() % 3)
        {
            case 0:
                try
                {
                    tree->insert(rand() % 5001 - 2500, std::move(""));
                }
                catch (std::exception const &ex)
                {
                    //std::cout << ex.what() << std::endl;
                }
                break;
            case 1:
                try
                {
                    ваще_пахую._key = rand() % 5001 - 2500;
                    tree->find(&ваще_пахую);
                }
                catch (std::exception const &ex)
                {
                    //std::cout << ex.what() << std::endl;
                }
                break;
            case 2:
                try
                {
                    auto поебать_ваще = tree->remove(rand() % 5001 - 2500);
                }
                catch (std::exception const &ex)
                {
                    //std::cout << ex.what() << std::endl;
                }
                break;
        }
    }
    delete tree;
}

void testing_bst()
{
    std::unique_ptr<builder> logger_builder = std::make_unique<builder_implementation>();

    auto logger = logger_builder->add_stream("logs.txt", fund_alg::logger::severity::trace)->build();

    std::shared_ptr<memory> allocator = std::make_shared<sorted_list_allocator>(1000000, memory::allocation_mode::first_match, logger.get());

    associative_container<int, int> * tree = new binary_search_tree<int, int, key_comparer>(allocator.get(), logger.get());

    *tree += associative_container<int, int>::key_value_pair{20, 20};
    *tree += associative_container<int, int>::key_value_pair{30, 30};
    *tree += associative_container<int, int>::key_value_pair{10, 10};
    *tree += associative_container<int, int>::key_value_pair{1, 1};
    *tree += associative_container<int, int>::key_value_pair{15, 15};
    *tree += associative_container<int, int>::key_value_pair{14, 14};
    *tree += associative_container<int, int>::key_value_pair{13, 13};
    *tree += associative_container<int, int>::key_value_pair{12, 12};
    *tree += associative_container<int, int>::key_value_pair{25, 25};

    tree->remove(10);

    auto end_infix = reinterpret_cast<binary_search_tree<int, int, key_comparer> *>(tree)->end_infix();
    for (auto it = reinterpret_cast<binary_search_tree<int, int, key_comparer> *>(tree)->begin_infix(); it != end_infix; ++it)
    {
        for (int i = 0; i < std::get<0>(*it); i++)
        {
            std::cout << "  ";
        }
        std::cout << std::get<2>(*it) << std::endl;
    }
    std::cout << std::endl;

}

void testing_splay_tree()
{
    std::unique_ptr<builder> logger_builder = std::make_unique<builder_implementation>();

    auto logger = logger_builder->add_stream("logs.txt", fund_alg::logger::severity::trace)->build();

    std::shared_ptr<memory> allocator = std::make_shared<sorted_list_allocator>(1000000, memory::allocation_mode::first_match, logger.get());

    associative_container<int, int> * tree = new splay_tree<int , int, key_comparer>(allocator.get(), logger.get());

    tree->insert(1, 1);
    tree->insert(16, 16);
    tree->insert(25, 25);
    tree->insert(4, 4);
    tree->insert(14, 14);

    auto tree1 = std::move(*reinterpret_cast<splay_tree<int, int, key_comparer> *>(tree));


    tree1.insert(15, 15);
    tree1.remove(15);

    delete tree;
}

void testing_avl_tree()
{
    std::unique_ptr<builder> logger_builder = std::make_unique<builder_implementation>();

    auto logger = logger_builder->add_stream("logs.txt", fund_alg::logger::severity::trace)->build();

    std::shared_ptr<memory> allocator = std::make_shared<sorted_list_allocator>(1000000, memory::allocation_mode::first_match, logger.get());

    auto * tree = new avl_tree<int , int, key_comparer>(allocator.get(), logger.get());

    tree->insert(10, 10);
    tree->insert(13, 13);
    tree->insert(1, 1);
    tree->insert(16, 16);
    tree->insert(25, 25);
    tree->insert(4, 4);
    tree->insert(14, 14);

    auto tree1 = std::move(*reinterpret_cast<avl_tree<int, int, key_comparer> *>(tree));

    delete tree;

    tree1.remove(10);
    tree1.remove(16);
}

void testing_rb_tree()
{
    std::unique_ptr<builder> logger_builder = std::make_unique<builder_implementation>();

    auto logger = logger_builder->add_stream("logs.txt", fund_alg::logger::severity::trace)->build();

    std::shared_ptr<memory> allocator = std::make_shared<sorted_list_allocator>(1000000, memory::allocation_mode::first_match, logger.get());

    auto * tree = new rb_tree<int , int, key_comparer>(allocator.get(), logger.get());

    delete tree;
}

int main()
{
    testing_rb_tree();

    return 0;
}
