#pragma once
#include <map>
#include <vector>
#include "datanivel.hpp"
#include "jugador.hpp"
#include "caja.hpp"

class Mapa {
    public:
        Mapa();

        int getTile(int x , int y);
        void setTile(int x, int y, int valor);

        grillaNivel getGrilla(){ return grillaMapa; }

        void setGrilla(const grillaNivel& nuevaGrilla){ 
            grillaMapa = nuevaGrilla;
            sincronizarCajas();
        } 

        bool nivelCompletado();
        bool cargarTexturas();
        void chequearBotones();
        void cargarNivel(const grillaNivel& nivel, Jugador& jugador);
        void renderizar(sf::RenderWindow& ventana);
        void sincronizarCajas();

    private: 
        std::map<int, sf::Texture> texturas;
        grillaNivel grillaMapa;
        int botonesPresionados;
        int botonesNecesarios;
        std::vector<Caja> cajas;
};