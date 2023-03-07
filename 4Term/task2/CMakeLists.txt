cmake_minimum_required(VERSION 3.24)
project(task2)

set(CMAKE_CXX_STANDARD 17)

add_executable(task2 main.cpp memory_implementation.cpp ../task1/logger_implementation.cpp ../task1/json_implementation.cpp)
