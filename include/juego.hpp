#pragma once
#include <SFML/Graphics.hpp>
#include "entidad.hpp"
#include "jugador.hpp"
#include "mapa.hpp"
#include "niveles.hpp"

enum class EstadoJuego {
    MENU,
    JUGANDO,
    SALIR
};

class Juego {
    public:
        Juego();
        void run();

    private:
        void manejarInput();
        void actualizar();
        void renderizar();

        sf::RenderWindow ventana;

        EstadoJuego estadoActual = EstadoJuego::MENU;
        Jugador jugador;
        Mapa mapa;
        Niveles niveles;

        int nivelActual;
};