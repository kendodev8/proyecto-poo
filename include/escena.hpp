#ifndef ESCENA
#define ESCENA
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>
#include <SFML/Window.hpp>

class Juego;

class Escena {
    public:
        virtual void actualizar(Juego &juego) = 0;
        virtual void renderizar(sf::RenderWindow &ventana) = 0;
        virtual void procesarEvento(Juego &juego, const sf::Event &evento) = 0;
};

#endif