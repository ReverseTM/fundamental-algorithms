#include <iostream>
#include "logger/logger_implementation.h"
#include "logger/builder_implementation.h"
#include "memory_allocators/global_heap_allocator.h"
#include "memory_allocators/sorted_list_allocator.h"
#include "memory_allocators/border_descriptors_allocator.h"
#include "memory_allocators/buddy_allocator.h"
#include <list>
#include <cmath>

void testing_allocator()
{
    builder *builder = new builder_implementation();


    fund_alg::logger *logger = builder
            ->add_stream("logs.txt", fund_alg::logger::severity::trace)
            ->build();

    memory *allocator1 = new global_heap_allocator(logger);
    memory *allocator2 = new border_descriptors_allocator(1000000, memory::allocation_mode::first_match, logger, allocator1);
    memory *allocator3 = new sorted_list_allocator(999900, memory::allocation_mode::the_best_match, logger, allocator2);
    memory * allocator4 = new buddy_system_allocator(17, memory::allocation_mode::first_match, logger, allocator3);

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

    delete allocator4;
    delete allocator3;
    delete allocator2;
    delete allocator1;
    delete logger;
    delete builder;
}


//!! About 11 task
//class A
//{
//
//protected:
//    class Summator
//    {
//    public:
//        int sum_template() {
//            std::cout << "sum_template" << std::endl;
//            sum_inner();
//        }
//
//    private:
//        int sum_inner() {
//            std::cout << "sum_inner" << std::endl;
//            sum_after_inner();
//        }
//
//    protected:
//        virtual int sum_after_inner()
//        {
//            std::cout << "sum_after_inner" << std::endl;
//        }
//
//    };
//private:
//    Summator *_summator;
//
//public:
//    A(A::Summator *sum_method) : _summator(sum_method) {};
//    A() : _summator(new Summator()) {};
//
//    virtual ~A() = default;
//
//    void sum()
//    {
//        _summator->sum_template();
//    }
//
//};
//
//class B : public A
//{
//protected:
//    class C : public A::Summator
//    {
//        int sum_after_inner() override
//        {
//            std::cout << "sum_after_inner class B" << std::endl;
//        }
//
//    };
//public:
//    B() : A(new C()) {};
//};

//Вызов фунции sum, которая дополнена в потомке
//A * ptr = new B();
//ptr->sum();

/*
 * постфиксный (лево право корень)
 * инфиксный (лево корень право)
 * префиксный(корень лево право)
 */


/*
 *  в конструкторе инфиксного итератора сразу спускаемся в самый левый узел
*/

/*
 * в свободных храним ( в одном байте(размер занятость), некст прев) unsigned char memory_size_power_2
 * в занятых храним (размер и занятость)
 */





/*
 * if (cur == null) return *this;
 *
 * if (left != null)
 * push in stack;
 * current_node = left;
 *
 *
 * else same  right
 *
 *
 * else
 *  while (true)
 *      if (stack empty) return nullptr
 *      break;
 *
 *      else stack.top
 *
 *
 *
 */







int main()
{

    testing_allocator();

//    builder * builder = new builder_implementation();
//    fund_alg::logger * logger = builder->add_stream("logs.txt", fund_alg::logger::severity::trace)->build();
//
//    memory * allocator = new buddy_system_allocator(16, memory::allocation_mode::first_match, logger);
//
//    auto ptr1 = allocator->allocate(69);
//    auto ptr2 = allocator->allocate(106);
//    auto ptr3 = allocator->allocate(104);
//    auto ptr4 = allocator->allocate(44);
//    allocator->deallocate(ptr2);
//    allocator->deallocate(ptr3);
//    auto ptr5 = allocator->allocate(118);
//    allocator->deallocate(ptr4); // посмотреть тут указатели
//    auto ptr6 = allocator->allocate(114);
//    allocator->deallocate(ptr5);
//    auto ptr7 = allocator->allocate(41);
//    auto ptr8 = allocator->allocate(103); //ptr8 ptr9 один адресс ??
//    auto ptr9 = allocator->allocate(102);
//    auto ptr10 = allocator->allocate(45);
//    auto ptr11 = allocator->allocate(91);
//    allocator->deallocate(ptr8);
//    auto ptr12 = allocator->allocate(116);
//    auto ptr13 = allocator->allocate(97);
//    allocator->deallocate(ptr12);
//    allocator->deallocate(ptr1);
//    auto ptr14 = allocator->allocate(143);


//    delete allocator;
//    delete logger;
//    delete builder;

    return 0;
}
