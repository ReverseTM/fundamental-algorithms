#include <iostream>
#include "memory_implementation.h"

int main() {
    memory *allocator = new memory_implementation();

    void *ptr = allocator->allocate(32);
    std::cout << ptr << std::endl;
    allocator->deallocate(ptr);
    delete allocator;
    return 0;
}
