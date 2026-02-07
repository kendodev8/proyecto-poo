#pragma once

#include <SFML/Graphics.hpp>
#include "../include/datanivel.hpp"
#include "../include/jugador.hpp"

class Mapa {
    private: 
        grillaNivel grillaMapa;
        
    public:
        Mapa();
        int getTile(int x , int y);
        void setTile(int x, int y, int valor);
        void cargarNivel(const grillaNivel& nivel, Jugador& jugador);
        void renderizar(sf::RenderWindow& ventana);
};