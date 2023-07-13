cmake_minimum_required(VERSION 3.24)
project(numpy_vs_cpp)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ltbb -lpthread -pthread -O0")

include_directories(.)

add_executable(numpy_vs_cpp
               main.cpp log_duration.h)

target_link_libraries(${PROJECT_NAME} PRIVATE tbb)
