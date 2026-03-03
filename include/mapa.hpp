#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <vector>
#include "../include/datanivel.hpp"
#include "../include/jugador.hpp"
#include "../include/caja.hpp"

class Mapa {
    public:
        Mapa();

        int getTile(int x , int y);
        void setTile(int x, int y, int valor);

        grillaNivel getGrilla(){ return grillaMapa; } // Evito sobrecarga

        void setGrilla(const grillaNivel& nuevaGrilla){ 
            grillaMapa = nuevaGrilla;
            sincronizarCajas();
        } 

        bool nivelCompletado(); //La clase Juego no tiene idea de cómo contar cajas ni cómo saber si ganaste, smplemente le pregunta al mapa: mapa.nivelCompletado()
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