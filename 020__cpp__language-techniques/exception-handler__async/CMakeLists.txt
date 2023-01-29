cmake_minimum_required(VERSION 3.9)
project(Exception_handler)
add_executable(exception_handler_async.elf main.cpp exception_handler.cpp)
target_link_libraries(exception_handler_async.elf PUBLIC pthread)
