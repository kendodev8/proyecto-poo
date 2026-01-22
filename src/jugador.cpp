//#include <cstdio>
#include "../include/jugador.hpp"

Jugador::Jugador() { 
    sprite.setSize({32.f, 32.f});
    sprite.setFillColor(sf::Color::Blue);
}

void Jugador::renderizar(sf::RenderWindow &ventana) { 
    sprite.setPosition(posInicial);
    //printf("Pos X: %f\n", posInicial.x);
    //printf("Pos Y: %f\n", posInicial.y);
    ventana.draw(sprite);
}