cmake_minimum_required(VERSION 3.0)

project(limit-order-book)

add_executable(limit-order-book main.cpp)

install(TARGETS limit-order-book RUNTIME DESTINATION bin)
