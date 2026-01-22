#include <SFML/Graphics.hpp>
#include <cstdio>
#include "../include/mapa.hpp"
#include "../include/niveles.hpp"
#include "../include/jugador.hpp"

int main() {
    sf::RenderWindow ventana(sf::VideoMode({512, 512}), "Sokoban");

    Niveles niveles;
    Mapa mapa;
    Jugador jugador;

    int nivelActual = 0;

    mapa.cargarNivel(niveles.getNivel(nivelActual), jugador);
    
    printf("Pos X: %f\n", jugador.getPosInicial().x);
    printf("Pos Y: %f\n", jugador.getPosInicial().y);

    while(ventana.isOpen()) {
        while(const std::optional event = ventana.pollEvent()){
            if(event->is<sf::Event::Closed>()){
                ventana.close();
            }
        }

        ventana.clear();
        mapa.renderizar(ventana);
        jugador.renderizar(ventana);
        ventana.display();
    }

    return 0;
}