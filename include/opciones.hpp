#ifndef OPCIONES
#define OPCIONES
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "escena.hpp"

class Opciones : public Escena {
    public:
        Opciones();
        void actualizar(Juego &juego) override;
        void renderizar(sf::RenderWindow &ventana) override;
        void procesarEvento(Juego &juego, const sf::Event &evento) override;

    private:
        sf::Font fuente;
        sf::Text textoVolver, textoSalir, textoVolumen;
        sf::RectangleShape barraVolumen;
        sf::Sprite sliderVolumen;
        sf::Texture texturaUI;

        int opcionSeleccionada; // 0: Volumen, 1: Volver a partida, 2: Salir a menú principal
        int nivelVolumen;
};

#endif