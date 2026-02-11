#pragma once
#include <SFML/Graphics.hpp>
#include "entidad.hpp"
#include "jugador.hpp"
#include "mapa.hpp"
#include "niveles.hpp"

struct Estado {
    grillaNivel copiaGrilla;
    sf::Vector2f posicionJugador;
};

class Juego {
    public:
        Juego();
        void run();

    private:
        void manejarInput();
        void actualizar();
        void renderizar();
        void intentarMover(int dx, int dy);
        void guardarEstado();
        void deshacerMovimiento();

        sf::RenderWindow ventana;

        Jugador jugador;
        Mapa mapa;
        Niveles niveles;
        std::vector<Estado> historial;

        int nivelActual;

        sf::Font fuente;
};