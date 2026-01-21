#include <SFML/Graphics.hpp>
#include "../include/mapa.hpp"

int main() {
    sf::RenderWindow ventana(sf::VideoMode({800, 600}), "Sokoban");

    Mapa mapa;

    int nivel1[4][4] = {
        {0, 0, 0, 0},
        {0, 1, 1, 0},
        {0, 1, 1, 0},
        {0, 0, 0, 0}
    };

    mapa.cargarNivel(nivel1);

    while (ventana.isOpen()) {
        while (const std::optional event = ventana.pollEvent()){
            if (event->is<sf::Event::Closed>()){
                ventana.close();
            }
        }

        ventana.clear();
        mapa.renderizar(ventana);
        ventana.display();
    }

    return 0;
}