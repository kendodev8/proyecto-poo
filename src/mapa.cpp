#include <cstdio>
#include "../include/mapa.hpp"

Mapa::Mapa(){

}

void Mapa::cargarNivel(const grillaNivel& nivel, Jugador& jugador){
    for(int y = 0; y < ALTO_MAX; y++){
        for(int x = 0; x < ANCHO_MAX; x++){
            grillaMapa[y][x] = nivel[y][x];

            if(grillaMapa[y][x] == 9){
                printf("Pos X: %i\n", x);
                printf("Pos Y: %i\n", y);
                jugador.setPosInicial({x * TAMAÑO_TILE, y * TAMAÑO_TILE});
                grillaMapa[y][x] = 0;
            }

            if(grillaMapa[y][x] == 8){
                grillaMapa[y][x] = 0;
            }
        }
    }
}

void Mapa::renderizar(sf::RenderWindow& ventana){
    sf::RectangleShape tile({TAMAÑO_TILE, TAMAÑO_TILE});
    
    for(int y = 0; y < ALTO_MAX; y++){
        for(int x = 0; x < ANCHO_MAX; x++){
            tile.setPosition({x * TAMAÑO_TILE, y * TAMAÑO_TILE});
            
            if(grillaMapa[y][x] == 0){
                tile.setFillColor(sf::Color::White);              
            }

            if(grillaMapa[y][x] == 1){
                tile.setFillColor(sf::Color::Green);
            }

            if(grillaMapa[y][x] == 2){
                tile.setFillColor(sf::Color::Yellow);
            }

            if(grillaMapa[y][x] == 3){
                tile.setFillColor(sf::Color::Magenta);
            }

            ventana.draw(tile);
        }
    }
}