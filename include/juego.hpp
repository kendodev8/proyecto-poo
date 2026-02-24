#pragma once
#include <SFML/Graphics.hpp>
#include "entidad.hpp"
#include "jugador.hpp"
#include "mapa.hpp"
#include "niveles.hpp"
#include <SFML/Audio.hpp>
#include <optional>

struct Estado {
    grillaNivel copiaGrilla;
    sf::Vector2f posicionJugador;
};

enum class Pantalla { MENU, JUGANDO, VICTORIA };

class Juego {
    public:
        Juego();
        void run();

    private:
        Pantalla pantallaActual;
        sf::Text textoVictoria;

        
        sf::SoundBuffer bufferSiguiente;
        std::optional<sf::Sound> sonidoSiguiente;

        sf::SoundBuffer bufferVictoria;
        std::optional<sf::Sound> sonidoVictoria;
        
        sf::Music musicaFondo;
        sf::SoundBuffer bufferMovimiento;
        std::optional<sf::Sound> sonidoMovimiento;

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