cmake_minimum_required(VERSION 2.8.10)

project(Fir CXX)

set(CMAKE_CXX_COMPILER /opt/local/bin/g++-4.8)
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -Werror -g -O0 ${CMAKE_CXX_FLAGS}")

include_directories(src include)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

add_executable(fir src/fir-cli.cpp)
