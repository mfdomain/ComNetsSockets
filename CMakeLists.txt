cmake_minimum_required(VERSION 3.12)
project(ComNetsSockets C)

set(CMAKE_C_STANDARD 99)

add_executable(ComNetsSockets proxy.c)
add_executable(ComNetsSockets2 client.c)