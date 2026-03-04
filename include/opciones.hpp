#ifndef OPCIONES
#define OPCIONES
#include "escena.hpp"

class Opciones : public Escena {
    public:
        Opciones();
        Opciones(bool vieneDelMenu = true);
        void actualizar(Juego &juego) override;
        void renderizar(sf::RenderWindow &ventana) override;
        void procesarEvento(Juego &juego, const sf::Event &evento) override;

    private:

        sf::Texture texturaFondoOpciones;
        sf::Sprite spriteFondoOpciones;
        
        sf::Font fuente;
        sf::Text textoVolver, textoSalir, textoVolumen;
        sf::RectangleShape barraVolumen;
        sf::RectangleShape sliderVolumen;
        sf::Texture texturaUI;

        

        bool desdeMenu;
        int opcionSeleccionada; // 0: Volumen, 1: Volver a partida, 2: Salir a menú principal
        int nivelVolumen;
};

#endif