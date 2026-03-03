#pragma once

#include <SFML/Graphics.hpp>
#include "../include/entidad.hpp"

class Jugador : public Entidad { //al heredar de Entidad, Jugador tiene acceso a sus atributos y métodos, como setPos/getPos
    public:
        Jugador();
        void renderizar(sf::RenderWindow& ventana);
        bool cargarTextura();

    private:
        sf::Texture texturaJugador;
};
