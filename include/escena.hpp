#ifndef ESCENA
#define ESCENA
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

class Juego;

class Escena {
    public:
        virtual void actualizar(Juego &juego) = 0;
        virtual void renderizar(sf::RenderWindow &ventana) = 0;
        virtual void procesarEvento(Juego &juego, const sf::Event &evento) = 0;
};

#endif