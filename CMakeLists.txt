cmake_minimum_required(VERSION 3.23)

project(snake
        VERSION 0.0.1.0
        LANGUAGES CXX
        HOMEPAGE_URL "https://github.com/khromenokroman/snake"
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

message(STATUS "CXX Compiler path: ${CMAKE_CXX_COMPILER}")
message(STATUS "CXX Compiler name: ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "CXX Compiler version: ${CMAKE_CXX_COMPILER_VERSION}")

add_definitions("-DVERSION_MAJOR=${PROJECT_VERSION_MAJOR}")
add_definitions("-DVERSION_MINOR=${PROJECT_VERSION_MINOR}")
add_definitions("-DVERSION_PATCH=${PROJECT_VERSION_PATCH}")
add_definitions("-DVERSION_TWEAK=${PROJECT_VERSION_TWEAK}")

set(CMAKE_VERBOSE_MAKEFILE ON)

add_custom_target(version
        -DVERSION_MAJOR="${PROJECT_VERSION_MAJOR}"
        -DVERSION_MINOR="${PROJECT_VERSION_MINOR}"
        -DVERSION_PATCH="${PROJECT_VERSION_PATCH}"
        -DVERSION_TWEAK="${PROJECT_VERSION_TWEAK}"
)

add_subdirectory(src)