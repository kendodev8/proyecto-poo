#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include "../include/datanivel.hpp"
#include "../include/jugador.hpp"

class Mapa {
    public:
        Mapa();

        int getTile(int x , int y);
        bool nivelCompletado();
        bool cargarTexturas();

        void chequearBotones();
        void setTile(int x, int y, int valor);
        void cargarNivel(const grillaNivel& nivel, Jugador& jugador);
        void renderizar(sf::RenderWindow& ventana);
    
    private: 
        std::map<int, sf::Texture> texturas;
        grillaNivel grillaMapa;
        int botonesPresionados;
        int botonesNecesarios;
};