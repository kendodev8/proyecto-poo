#ifndef SCOREBOARD
#define SCOREBOARD
#include <SFML/Graphics.hpp>
#include "escena.hpp"

class Scoreboard : public Escena {
    public:
        Scoreboard();
        void actualizar(Juego &juego) override;
        void renderizar(sf::RenderWindow &ventana) override;
        void procesarEvento(Juego &juego, const sf::Event &evento) override;
    
    private:
        sf::Font fuente;
        sf::Text textoNivel;
        std::vector<sf::Text> textoScores;

        int opcionSeleccionada;
};


#endif