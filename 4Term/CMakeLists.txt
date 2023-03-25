cmake_minimum_required(VERSION 3.24)
project(project)

set(CMAKE_CXX_STANDARD 17)

add_executable(project main.cpp logger/builder_implementation.cpp logger/logger_implementation.cpp logger/json_implementation.cpp memory_allocators/memory.cpp memory_allocators/global_heap/global_heap_memory.cpp memory_allocators/sorted_list/sorted_list_memory.cpp)
