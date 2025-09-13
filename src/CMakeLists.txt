find_package(raylib REQUIRED)

add_executable(${PROJECT_NAME}
        main.cpp
        food.cpp
        snake.cpp
        game.cpp
)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)


install(TARGETS ${PROJECT_NAME}
        DESTINATION bin
)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/sounds
        DESTINATION share/${PROJECT_NAME}/
)
install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bitmaps
        DESTINATION share/${PROJECT_NAME}/
)