#pragma once
#include <SFML/Graphics.hpp>
#include "entidad.hpp"
#include "jugador.hpp"
#include "mapa.hpp"
#include "niveles.hpp"
#include <SFML/Audio.hpp>
#include <optional>

struct Estado { //este nos sirve para guardar el estado del juego cada vez que el jugador hace un movimiento, para poder deshacerlo después
    grillaNivel copiaGrilla;
    sf::Vector2f posicionJugador;
};

enum class Pantalla { MENU, OPCIONES, JUGANDO, VICTORIA };

class Juego {
    public:
        Juego();
        void run();

    private:
        
        //SONIDOS Q LE PUSIMOS:
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
        sf::Text textoSalir;
        sf::Sprite botonVolver;
        sf::Text textoVolver;
        sf::RectangleShape barraVolumenFondo;
        sf::Sprite perillaVolumen;
        sf::Text textoVolumen;
        int opcionSeleccionada; // 0 o 1 (para saber qué botón brilla)
        int nivelVolumen;       // Del 0 al 10, tranqui nomas 

        // In-Game
        sf::Sprite spriteAjustes; // La tuerca en la esquina
        sf::Text textoNivelUI;

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
        std::vector<Estado> historial; //aca guardo una foto del estado del juego cada vez que el jugador hace un movimiento, para poder deshacerlo después

        int nivelActual;

        sf::Font fuente;
};