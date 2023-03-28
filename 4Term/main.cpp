#include <iostream>
#include "logger/logger_implementation.h"
#include "logger/builder_implementation.h"
#include "memory_allocators/global_heap/global_heap_memory.h"
#include "memory_allocators/sorted_list/sorted_list_memory.h"

void test_allocators()
{
    builder *builder = new builder_implementation();


    fund_alg::logger *logger = builder
            ->add_stream("logs.txt", fund_alg::logger::severity::trace)
            ->build();

    memory *allocator1 = new global_heap_allocator(logger);
    memory *allocator2 = new sorted_list_memory(100, memory::allocation_mode::first_match, logger, allocator1);

    int *number = reinterpret_cast<int*>(allocator2->allocate(sizeof(int)));
    *number = 5;

    int *number2 = reinterpret_cast<int*>(allocator2->allocate(sizeof(int)));
    *number2 = 10;

    int *number3 = reinterpret_cast<int*>(allocator2->allocate(sizeof(int)));
    *number3 = 15;

    allocator2->deallocate(reinterpret_cast<void*>(number));
    allocator2->deallocate(reinterpret_cast<void*>(number2));
    allocator2->deallocate(reinterpret_cast<void*>(number3));

    delete allocator2;
    delete allocator1;
    delete logger;
    delete builder;
}

int main() {

    test_allocators();

    return 0;
}
