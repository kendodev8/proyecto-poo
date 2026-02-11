#include <iostream>
#include "../include/jugador.hpp"

Jugador::Jugador()
{ 
    if(!texturaJugador.loadFromFile("./assets/jugador.png")){
        std::cerr << "Error cargando jugador.png" << std::endl;
    }
}

void Jugador::setPos(sf::Vector2f pos){
    posicion = pos;
}

void Jugador::renderizar(sf::RenderWindow &ventana){
    sf::Sprite spriteJugador(texturaJugador);
    spriteJugador.setPosition(posicion);
    ventana.draw(spriteJugador);
}

sf::Vector2f Jugador::getPos(){
    return posicion;
}
