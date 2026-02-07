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

void Mapa::renderizar(sf::RenderWindow& ventana) {
    for (int y = 0; y < ALTO_MAX; y++) {
        for (int x = 0; x < ANCHO_MAX; x++) {
            
            int tipo = grillaMapa[y][x];
            sf::RectangleShape celda(sf::Vector2f({32.f, 32.f}));
            celda.setPosition({x * 32.f, y * 32.f});

            switch (tipo) {
                case 0: celda.setFillColor(sf::Color::White); break; 
                case 1: celda.setFillColor(sf::Color::Blue); break; //lo deje azul porq queria hacer verde la win
                case 2: celda.setFillColor(sf::Color::Yellow); break;  
                case 3: celda.setFillColor(sf::Color::Magenta); break; 
                case 4: celda.setFillColor(sf::Color::White); break; //para la meta bro
                case 5: celda.setFillColor(sf::Color::Green); break; //cuando la caja esta lista
            }
            ventana.draw(celda);

            // Si es una meta, un puntito rojo encima
            if (tipo == 4) {
                sf::CircleShape punto(8.f); // Radio de 8 pixeles fue
                punto.setFillColor(sf::Color::Red);
                punto.setPosition({x * 32.f + 8, y * 32.f + 8}); // Centrado
                ventana.draw(punto);
            }
        }
    }
}

int Mapa::getTile(int x,int y){
    if (x<0 || x>=ANCHO_MAX || y<0 || y>= ALTO_MAX){ //fuera del mapita 
        return 1;
    }
    return grillaMapa[y][x]; //dentro del mapita pa
}

void Mapa::setTile(int x, int y, int valor) {
    if (x >= 0 && x < ANCHO_MAX && y >= 0 && y < ALTO_MAX) {
        grillaMapa[y][x] = valor;
    }
}

