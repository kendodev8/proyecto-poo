cmake_minimum_required(VERSION 3.16)
project(sokoban LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 3.0.2 COMPONENTS Graphics Window Audio System REQUIRED)

add_executable(game
    src/main.cpp
    src/mapa.cpp
)

target_include_directories(game PRIVATE include)

target_link_libraries(game
    SFML::Graphics
    SFML::Window
    SFML::Audio
    SFML::System
)
