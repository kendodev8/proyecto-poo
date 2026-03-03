#include <iostream>
#include "../include/jugador.hpp"

Jugador::Jugador()
{ 
    if(!texturaJugador.loadFromFile("./assets/jugador.png")){
        std::cerr << "Error cargando jugador.png" << std::endl;
    }
}

void Jugador::renderizar(sf::RenderWindow &ventana){

    sf::Sprite spriteJugador(texturaJugador);

    spriteJugador.setPosition(posInicial);

    ventana.draw(spriteJugador);

}

