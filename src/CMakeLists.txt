find_package(raylib REQUIRED)

add_executable(snake
        main.cpp
        food.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)