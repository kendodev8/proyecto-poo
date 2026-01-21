#include "../include/mapa.hpp"

Mapa::Mapa(){

}

void Mapa::cargarNivel(int nivel[ANCHO_MAX][ALTO_MAX]){
    for(int i = 0; i < ANCHO_MAX; i++){
        for(int j = 0; j < ALTO_MAX; j++){
            mapa[i][j] = nivel[i][j];
        }
    }
}

void Mapa::renderizar(sf::RenderWindow& ventana){
    sf::RectangleShape tile({TAMAÑO_TILE, TAMAÑO_TILE});
    
    for(int i = 0; i < ANCHO_MAX; i++){
        for(int j = 0; j < ALTO_MAX; j++){
            tile.setPosition({i * TAMAÑO_TILE, j * TAMAÑO_TILE});
            
            if(mapa[i][j] == 0){
                tile.setFillColor(sf::Color::White);              
            }

            if (mapa[i][j] == 1){
                tile.setFillColor(sf::Color::Green);
            }

            ventana.draw(tile);
        }
    }
}