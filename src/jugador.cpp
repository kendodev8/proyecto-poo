//#include <cstdio>
#include "../include/jugador.hpp"

Jugador::Jugador() { 
    sprite.setSize({32.f, 32.f});
    sprite.setFillColor(sf::Color::Blue);
}

void Jugador::setPosInicial(sf::Vector2f pos) {
    this->posInicial = pos; //pr si reinicio el lvl
    sprite.setPosition(pos);
}

void Jugador::renderizar(sf::RenderWindow &ventana) { 
    //sprite.setPosition(posInicial);
    //printf("Pos X: %f\n", posInicial.x);
    //printf("Pos Y: %f\n", posInicial.y);
    ventana.draw(sprite);
}

void Jugador::mover(float x,float y){
    sprite.move({x,y});
}

sf::Vector2f Jugador::getPosInicial() {
    return this->posInicial;
}