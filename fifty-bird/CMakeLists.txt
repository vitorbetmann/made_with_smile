cmake_minimum_required(VERSION 4.2)
project(fifty-bird C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(raylib REQUIRED)

add_executable(fifty-bird
        main.c

        src/Bird.c
        src/Pipe.c
        src/PipePair.c
        src/Settings.c
        src/PipeManager.c

        src/scenes/Title.c
        src/scenes/Countdown.c
        src/scenes/Play.c
        src/scenes/Pause.c
        src/scenes/Score.c
)

add_subdirectory(smile)

target_include_directories(fifty-bird PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/smile/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/include/scenes
)

target_link_libraries(fifty-bird PRIVATE
        smile
        raylib
)