#include <iostream>
#include "logger/logger_implementation.h"
#include "logger/builder_implementation.h"
#include "memory_allocators/global_heap_allocator.h"
#include "memory_allocators/sorted_list_allocator.h"

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

    delete allocator1;
    delete logger;
    delete builder;
}

void test_sorted_list_allocator()
{
    builder *builder = new builder_implementation();


    fund_alg::logger *logger = builder
            ->add_stream("logs.txt", fund_alg::logger::severity::trace)
            ->build();

    memory *allocator1 = new global_heap_allocator(logger);
    memory *allocator2 = new sorted_list_allocator(100, memory::allocation_mode::first_match, logger, allocator1);

    void * ptr = reinterpret_cast<void*>(allocator2->allocate(50));
    void * ptr2 = reinterpret_cast<void*>(allocator2->allocate(50));

    allocator2->deallocate(ptr);
    void * ptr3 = reinterpret_cast<void*>(allocator2->allocate(21));
    void * ptr4 = reinterpret_cast<void*>(allocator2->allocate(21));

    allocator2->deallocate(ptr3);
    allocator2->deallocate(ptr4);

    void * ptr5 = reinterpret_cast<void*>(allocator2->allocate(50));

    allocator2->deallocate(ptr2);
    allocator2->deallocate(ptr5);

    int * number = reinterpret_cast<int*>(allocator2->allocate(sizeof(int)));
    *number = 1234;
    allocator2->deallocate(number);

//    void * block = reinterpret_cast<void*>((*allocator1) += 5);
//    allocator2->deallocate(block);
//    *allocator1 -= block;

    delete allocator2;
    delete allocator1;
    delete logger;
    delete builder;
}


int main() {

    test_sorted_list_allocator();

    return 0;
}
