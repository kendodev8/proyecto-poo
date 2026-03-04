#ifndef VICTORIA
#define VICTORIA
#include "escena.hpp"

class Victoria : public Escena {
public:
    Victoria();
    void actualizar(Juego &juego) override;
    void renderizar(sf::RenderWindow &ventana) override;
    void procesarEvento(Juego &juego, const sf::Event &evento) override;

private:
    sf::Texture texturaFondoVictoria;
    sf::RectangleShape fondoVictoria;
    sf::Font fuente;
    sf::Text textoVictoria;
    sf::Text textoSalir;
};

#endif 