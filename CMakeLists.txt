cmake_minimum_required (VERSION 2.8.11)
project (hw1)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g")

include_directories (include)
add_executable (hw1 src/hw1.cc src/Context.cc)
