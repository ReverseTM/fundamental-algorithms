#include <iostream>
#include "logger/logger_implementation.h"
#include "logger/builder_implementation.h"
#include "memory_allocators/global_heap_allocator.h"
#include "memory_allocators/sorted_list_allocator.h"
#include "memory_allocators/border_descriptors_allocator.h"
#include "memory_allocators/buddy_allocator.h"
#include "tree/binary_search_tree.h"
#include <list>

/*
            About 11 task
class A
{

protected:
    class Summator
    {
    public:
        int sum_template() {
            std::cout << "sum_template" << std::endl;
            sum_inner();
        }

    private:
        int sum_inner() {
            std::cout << "sum_inner" << std::endl;
            sum_after_inner();
        }

    protected:
        virtual int sum_after_inner()
        {
            std::cout << "sum_after_inner" << std::endl;
        }

    };
private:
    Summator *_summator;

public:
    A(A::Summator *sum_method) : _summator(sum_method) {};
    A() : _summator(new Summator()) {};

    virtual ~A() = default;

    void sum()
    {
        _summator->sum_template();
    }

};

class B : public A
{
protected:
    class C : public A::Summator
    {
        int sum_after_inner() override
        {
            std::cout << "sum_after_inner class B" << std::endl;
        }

    };
public:
    B() : A(new C()) {};
};

Вызов фунции sum, которая дополнена в потомке
A * ptr = new B();
ptr->sum();
*/

/*
 * постфиксный (лево право корень)
 * инфиксный (лево корень право)
 * префиксный(корень лево право)
 */

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

void testing_bst()
{
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

    std::unique_ptr<builder> logger_builder = std::make_unique<builder_implementation>();

    auto logger = logger_builder->add_stream("logs.txt", fund_alg::logger::severity::trace)->build();

    std::shared_ptr<memory> allocator = std::make_shared<sorted_list_allocator>(1000000, memory::allocation_mode::first_match, logger.get());

    associative_container<int, int> * tree = new binary_search_tree<int , int, key_comparer>(allocator.get(), logger.get());

    tree->insert(6, 6);
    tree->insert(2, 2);
    tree->insert(10, 10);
    tree->insert(1, 1);
    tree->insert(4, 4);
    tree->insert(7, 7);
    tree->insert(12, 12);
    tree->insert(3, 3);
    tree->insert(11, 11);

    auto tree1 = *reinterpret_cast<binary_search_tree<int, int, key_comparer>*>(tree);

    auto end_infix = tree1.end_infix();
    for (auto it = tree1.begin_infix(); it != end_infix; ++it)
    {
        for (int i = 0; i < std::get<0>(*it); i++)
        {
            std::cout << "  ";
        }
        std::cout << std::get<2>(*it) << std::endl;
    }
    std::cout << std::endl;

    delete tree;
}

int main()
{
    testing_bst();

    return 0;
}
