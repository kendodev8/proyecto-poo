#ifndef PARTIDA
#define PARTIDA
#include "escena.hpp"
#include "mapa.hpp"
#include "jugador.hpp"
#include "niveles.hpp"
#include <SFML/Audio.hpp>

struct Estado {
    grillaNivel copiaGrilla;
    sf::Vector2f posicionJugador;
};

class Partida : public Escena {
    public:
        Partida();
        void actualizar(Juego &juego) override;
        void renderizar(sf::RenderWindow &ventana) override;
        void procesarEvento(Juego &juego, const sf::Event &evento) override;

    private:
        void intentarMover(const int &dx, const int &dy);
        void deshacerMovimiento();
        void guardarEstado();

        sf::Font fuente;
        sf::Text textoMovimientos, textoNivel;
        
        sf::SoundBuffer bufferPaso;
        sf::Sound sonidoPaso;
        sf::SoundBuffer bufferNivel;
        sf::Sound sonidoNivel;

        Mapa mapa;
        Jugador jugador;
        Niveles niveles;
        std::vector<Estado> historial;

        int nivelActual, movimientos;
};

#endif