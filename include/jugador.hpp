#pragma once

#include <SFML/Graphics.hpp>
#include "../include/entidad.hpp"

class Jugador {
    public:
        Jugador();
        void renderizar(sf::RenderWindow& ventana);
        void setPos(sf::Vector2f pos);

        bool cargarTextura();
        sf::Vector2f getPos();

    private:
        sf::Texture texturaJugador;
        sf::Vector2f posicion;
};
