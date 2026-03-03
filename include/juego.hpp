#pragma once
#include <SFML/Graphics.hpp>
#include "escena.hpp"
#include "entidad.hpp"
#include "jugador.hpp"
#include "mapa.hpp"
#include "niveles.hpp"
#include <SFML/Audio.hpp>
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

        //Pantalla pantallaActual;
        //Pantalla pantallaAnterior;

        // --- COSAS VISUALES DEL MENÚ Y OPCIONES ---
        sf::Texture texturaFondoMenu;
        sf::Texture texturaUI;
        sf::Texture texturaAjustes; //Creo q este no lo usamos ya, era pq habia una tuerca en la esquina para volver al menú
        sf::Text textoVictoria;
        sf::Texture texturaFondoVictoria;

        // Menú Principal
        sf::Sprite spriteFondoMenu;
        sf::Sprite botonJugar;
        sf::Text textoJugar;
        sf::Sprite botonOpciones;
        sf::Text textoOpciones;
        sf::RectangleShape fondoVictoria;

        // Pantalla de Opciones
        sf::Text textoSalir, textoVolver, textoVolumen;
        sf::Text textoNivelUI;
        sf::Sprite botonVolver;
        sf::RectangleShape barraVolumenFondo;
        sf::Sprite perillaVolumen;
        int opcionSeleccionada;     // 0 o 1 (para saber qué botón brilla)
        int nivelVolumen;           // Del 0 al 10

        // In-Game
        //sf::Sprite spriteAjustes;

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
        //std::vector<Estado> historial;

        int nivelActual;

        sf::Font fuente;

        Escena *escena, *siguiente = nullptr;
};