cmake_minimum_required(VERSION 3.24)
project(kursovaya)

set(CMAKE_CXX_STANDARD 20)

add_executable(kursovaya
        main.cpp
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
        tree/associative_container.h
        tree/binary_search_tree.h
        tree/splay_tree.h
        compare/string_comparer.cpp
        compare/key_comparator.cpp
        containers/data_collection.cpp
        containers/scheme.cpp
        containers/pool.cpp
        containers/data_base.cpp
        types/data_type.h
        types/allocator_types.h
        request_handler_with_command_chain/command_add_collection.cpp
        request_handler_with_command_chain/command_add_data.cpp
        request_handler_with_command_chain/command_add_pool.cpp
        request_handler_with_command_chain/command_add_scheme.cpp
        request_handler_with_command_chain/command_get_data.cpp
        request_handler_with_command_chain/command_get_data_between.cpp
        request_handler_with_command_chain/command_remove_collection.cpp
        request_handler_with_command_chain/command_remove_data.cpp
        request_handler_with_command_chain/command_remove_pool.cpp
        request_handler_with_command_chain/command_remove_scheme.cpp
        request_handler_with_command_chain/command_update_data.cpp
        request_handler_with_command_chain/handler.h
        request_handler_with_command_chain/request_handler_with_command.cpp
        request_handler_with_command_chain/request_handler_with_command_chain.cpp
        request_handler_with_command_chain/command.cpp)
