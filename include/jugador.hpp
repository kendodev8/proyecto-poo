#pragma once

#include <SFML/Graphics.hpp>
#include "../include/entidad.hpp"

class Jugador : public Entidad {
    public:
        Jugador();
        void renderizar(sf::RenderWindow& ventana);
        bool cargarTextura();

    private:
        sf::Texture texturaJugador;
};
