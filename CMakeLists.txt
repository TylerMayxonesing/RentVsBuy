cmake_minimum_required(VERSION 3.14)
project(RentVsBuy)

set(CMAKE_CXX_STANDARD 14)

add_executable(RentVsBuy main.cpp RentVsBuy.cpp RentVsBuy.h)
add_compile_options(RentVsBuy PRIVATE -Wall -Werror)