#pragma once
#include "escena.hpp"
#include "entidad.hpp"
#include "jugador.hpp"
#include "mapa.hpp"
#include "niveles.hpp"
#include "scoremanager.hpp"
#include <SFML/Window.hpp>
#include <optional>

/*struct Estado {
    grillaNivel copiaGrilla;
    sf::Vector2f posicionJugador;
};*/

//enum class Pantalla { MENU, OPCIONES, JUGANDO, VICTORIA };

class Juego {
    public:
        Juego(Escena *primerEscena);
        void cambiarEscena(Escena *siguienteEscena);
        void run();
        void pausarJuego(Escena* menuPausa);
        void reanudarJuego();
        std::vector<score> getRegistroScores(){ return scoreManager.getScores(); }
        void setRegistroScores(const int &nivel, const int &movimientos, const std::string &nombre){ scoreManager.setScore(nivel, movimientos, nombre); }
        std::string getNombreJugador(){ return nombreJugador; }
        void setNombreJugador(std::string nombre) { nombreJugador = nombre; }
        ~Juego();

    private:
        /*sf::SoundBuffer bufferSelect;
        std::optional<sf::Sound> sonidoSelect;

        sf::SoundBuffer bufferSiguiente;
        std::optional<sf::Sound> sonidoSiguiente;

        sf::SoundBuffer bufferVictoria;
        std::optional<sf::Sound> sonidoVictoria;
        
        sf::Music musicaFondo;
        sf::SoundBuffer bufferMovimiento;
        std::optional<sf::Sound> sonidoMovimiento;*/

        // In-Game

        void manejarInput();
        void intentarMover(int dx, int dy);
        void guardarEstado();
        void deshacerMovimiento();

        sf::RenderWindow ventana;

        std::string nombreJugador;

        Jugador jugador;
        Mapa mapa;
        Niveles niveles;
        ScoreManager scoreManager;

        Escena *escena, *siguiente = nullptr;
        Escena *escenaPausada = nullptr;

        bool pausando = false;
};