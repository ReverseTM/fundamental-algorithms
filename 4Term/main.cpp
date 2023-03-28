#include <iostream>
#include "logger/logger_implementation.h"
#include "logger/builder_implementation.h"
#include "memory_allocators/global_heap_allocator.h"
#include "memory_allocators/sorted_list_allocator.h"
#include <list>

void test_global_heap_allocator()
{
    builder *builder = new builder_implementation();


    fund_alg::logger *logger = builder
            ->add_stream("logs.txt", fund_alg::logger::severity::trace)
            ->build();

    memory *allocator1 = new global_heap_allocator(logger);
    int * ptr = reinterpret_cast<int*>((*allocator1) += 4);
    *ptr = 5;
    *allocator1 -= ptr;

    std::string * str = reinterpret_cast<std::string*>((*allocator1) += sizeof(std::string));

    new(str) std::string("hello"); // ВЫЗОВ КОНСТРУКТОРА В СЫРОЙ ПАМЯТИ

    delete allocator1;
    delete logger;
    delete builder;
}

void testing_sorted_list_allocator()
{
    builder *builder = new builder_implementation();


    fund_alg::logger *logger = builder
            ->add_stream("logs.txt", fund_alg::logger::severity::trace)
            ->build();

    memory *allocator = new sorted_list_allocator(1000000, memory::allocation_mode::first_match, logger);

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
                    ptr = reinterpret_cast<void *>(allocator->allocate(rand() % 81 + 20)); // разность макс и мин с включенными границами + минимальное
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
                    allocator->deallocate(*iter);
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
            allocator->deallocate(*iter);
            allocated_blocks.erase(iter);
        }
        catch (std::exception const &ex)
        {
            std::cout << ex.what() << std::endl;
        }
    }

    delete allocator;
    delete logger;
    delete builder;
}

void sorted_list_allocator_demo()
{
    builder *builder = new builder_implementation();


    fund_alg::logger *logger = builder
            ->add_stream("logs.txt", fund_alg::logger::severity::trace)
            ->build();

    memory *allocator1 = new global_heap_allocator(logger);
    memory *allocator2 = new sorted_list_allocator(100, memory::allocation_mode::first_match, logger, allocator1);

    void * ptr1 = reinterpret_cast<void*>(allocator2->allocate(28));
    void * ptr2 = reinterpret_cast<void*>(allocator2->allocate(26));
    void * ptr3 = reinterpret_cast<void*>(allocator2->allocate(27));

    allocator2->deallocate(ptr1);
    allocator2->deallocate(ptr3);
    allocator2->deallocate(ptr2);

    delete allocator2;
    delete allocator1;
    delete logger;
    delete builder;
}


int main() {

    //testing_sorted_list_allocator();
    sorted_list_allocator_demo();

    return 0;
}
