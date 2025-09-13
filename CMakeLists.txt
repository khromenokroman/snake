cmake_minimum_required(VERSION 4.0)
project(snake)

find_package(raylib REQUIRED)

set(CMAKE_CXX_STANDARD 20)

add_executable(snake main.cpp)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)