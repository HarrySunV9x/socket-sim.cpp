# Ubuntu 22.04的cmake版本为3.22.1
cmake_minimum_required(VERSION 3.22)
project(socket_sim_cpp)

# 检测操作系统类型
if(UNIX AND NOT APPLE)
    message(STATUS "Building on Linux")
    add_definitions(-DPLATFORM_LINUX)
elseif(WIN32)
    message(STATUS "Building on Windows")
    add_definitions(-DPLATFORM_WINDOWS)
endif()

set(CMAKE_CXX_STANDARD 17)

set(APP_NAME "socket_sim_cpp")
add_definitions(-DAPP_NAME="socket_sim_cpp")
add_definitions(-DAPP_VERSION="0.0.1")

include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(src)