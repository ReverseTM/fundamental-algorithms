cmake_minimum_required(VERSION 3.24)
project(project)

set(CMAKE_CXX_STANDARD 17)

add_executable(project main.cpp
        logger/builder_implementation.cpp
        logger/logger_implementation.cpp
        logger/json_implementation.cpp
        logger/logger_holder.cpp
        memory_allocators/memory.cpp
        memory_allocators/global_heap_allocator.cpp
        memory_allocators/sorted_list_allocator.cpp
        memory_allocators/border_descriptors_allocator.cpp
        memory_allocators/buddy_allocator.cpp
        memory_allocators/memory_holder.cpp
        long_numbers/big_int.cpp
        tree/associative_container.h
        tree/binary_search_tree.h
        tree/splay_tree.h
        tree/avl_tree.h
        tree/red_black_tree.h)
