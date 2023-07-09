cmake_minimum_required(VERSION 3.24)
project(np_decoder)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(np_decoder
        main.cpp)
