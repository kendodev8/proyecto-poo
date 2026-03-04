cmake_minimum_required(VERSION 3.16)
project(sokoban LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 3.0.2 COMPONENTS Graphics Window Audio System REQUIRED)

add_executable(sokoban
    src/main.cpp
    src/juego.cpp
    src/menu.cpp
    src/opciones.cpp
    src/scoreboard.cpp
    src/inputnombre.cpp
    src/partida.cpp
    src/victoria.cpp
    src/mapa.cpp
    src/niveles.cpp
    src/jugador.cpp
    src/caja.cpp
    src/scoremanager.cpp
)

target_include_directories(sokoban PRIVATE include)

target_link_libraries(sokoban
    SFML::Graphics
    SFML::Window
    SFML::Audio
    SFML::System
)
