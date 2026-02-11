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
    std::cout << "Posicion: (" << spriteJugador.getPosition().x << ", " << spriteJugador.getPosition().y << ")" << std::endl;
    std::cout << "Escala: (" << spriteJugador.getScale().x << ", " << spriteJugador.getScale().y << ")" << std::endl;
    
    auto bounds = spriteJugador.getGlobalBounds();
    std::cout << "Bounds position: (" << bounds.position.x << ", " << bounds.position.y << std::endl;
    std::cout << "Bounds size: (" << bounds.size.x << ", " << bounds.size.y << ")" << std::endl;
    ventana.draw(spriteJugador);
}

sf::Vector2f Jugador::getPos(){
    return posicion;
}
