cmake_minimum_required (VERSION 2.8.11)
project (hw1)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


find_package ( Boost REQUIRED COMPONENTS regex system date_time )

include_directories (include ${Boost_INCLUDE_DIR})
add_executable (hw1 src/hw1.cc)
