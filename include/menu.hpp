#ifndef MENU
#define MENU
#include <optional>
#include "escena.hpp"

class Menu : public Escena {
    public:
        Menu();
        void actualizar(Juego &juego) override;
        void renderizar(sf::RenderWindow &ventana) override;
        void procesarEvento(Juego &juego, const sf::Event &evento) override;

    private:
        sf::Font fuente;
        sf::Text textoJugar, textoScoreboard, textoOpciones;
        sf::Texture texturaFondoMenu;
        sf::Sprite spriteFondoMenu;

        int opcionSeleccionada;

        sf::SoundBuffer selectBuffer;
        std::optional<sf::Sound> sonidoSelect;
};

#endif