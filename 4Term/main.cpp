#include <iostream>
#include "logger/logger_implementation.h"
#include "logger/builder_implementation.h"
#include "memory_allocators/global_heap/global_heap_memory.h"
#include "memory_allocators/sorted_list/sorted_list_memory.h"

int main() {

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
    std::cout << *number << " " << *number2 << std::endl;
    void *ptr = allocator2->allocate(0);

    allocator2->deallocate(number);
    allocator2->deallocate(number2);
    allocator2->deallocate(ptr);

    delete allocator2;
    delete allocator1;
    delete logger;
    delete builder;

    return 0;
}
