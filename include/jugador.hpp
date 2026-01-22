#pragma once

#include <SFML/Graphics.hpp>
#include "../include/entidad.hpp"

class Jugador : public Entidad {
    public:
        Jugador();

        void actualizar(float deltaTime);
        void renderizar(sf::RenderWindow& ventana);

    private:
        sf::RectangleShape sprite;
};
