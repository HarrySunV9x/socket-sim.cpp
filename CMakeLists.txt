# Ubuntu 22.04的cmake版本为3.22.1
cmake_minimum_required(VERSION 3.22)
project(socket_sim_cpp)

set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(socket main.cpp)
