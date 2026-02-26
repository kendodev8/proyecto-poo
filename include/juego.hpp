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

enum class Pantalla { MENU, OPCIONES, JUGANDO, VICTORIA };

class Juego {
    public:
        Juego();
        void run();

    private:
        
        sf::SoundBuffer bufferSelect;
        std::optional<sf::Sound> sonidoSelect;

        sf::SoundBuffer bufferSiguiente;
        std::optional<sf::Sound> sonidoSiguiente;

        sf::SoundBuffer bufferVictoria;
        std::optional<sf::Sound> sonidoVictoria;
        
        sf::Music musicaFondo;
        sf::SoundBuffer bufferMovimiento;
        std::optional<sf::Sound> sonidoMovimiento;

        Pantalla pantallaActual;
        Pantalla pantallaAnterior; // Para saber a dónde volver (al menú o al juego)

        sf::Text textoVictoria;

        // --- COSAS VISUALES DEL MENÚ Y OPCIONES ---
        sf::Texture texturaFondoMenu;
        sf::Texture texturaUI;
        sf::Texture texturaAjustes;
        sf::Texture texturaFondoVictoria;

        // Menú Principal
        sf::Sprite spriteFondoMenu;
        sf::Sprite botonJugar;
        sf::Text textoJugar;
        sf::Sprite botonOpciones;
        sf::Text textoOpciones;
        sf::RectangleShape fondoVictoria;

        // Pantalla de Opciones
        sf::Text textoSalir;
        sf::Text textoNivelUI; //capaz lo pongo en In-Game
        sf::Sprite botonVolver;
        sf::Text textoVolver;
        sf::RectangleShape barraVolumenFondo;
        sf::Sprite perillaVolumen;
        sf::Text textoVolumen;
        int opcionSeleccionada; // 0 o 1 (para saber qué botón brilla)
        int nivelVolumen;       // Del 0 al 10

        // In-Game
        sf::Sprite spriteAjustes; // La tuerca en la esquina

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