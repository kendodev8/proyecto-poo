#ifndef INPUTNOMBRE
#define INPUTNOMBRE
#include "escena.hpp"

class InputNombre : public Escena {
    public:
        InputNombre();
        void actualizar(Juego &juego) override;
        void renderizar(sf::RenderWindow &ventana) override;
        void procesarEvento(Juego &juego, const sf::Event &evento) override;

    private:
        sf::Font fuente;
        std::string nombreJugador;
        sf::Text textoNombre, textoInstruccion;
};

#endif