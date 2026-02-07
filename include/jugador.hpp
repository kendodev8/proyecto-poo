#pragma once

#include <SFML/Graphics.hpp>
#include "../include/entidad.hpp"

class Jugador : public Entidad {
    public:
        Jugador();
        void mover(float x,float y);
        void actualizar(float deltaTime);
        void renderizar(sf::RenderWindow& ventana);
        void setPosInicial(sf::Vector2f pos);
        sf::Vector2f getPosInicial();

    private:
        sf::RectangleShape sprite;
        sf::Vector2f posInicial;
};
