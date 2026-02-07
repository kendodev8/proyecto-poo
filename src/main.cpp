#include <SFML/Graphics.hpp>
#include <string> 
#include "../include/mapa.hpp"
#include "../include/jugador.hpp"
#include "../include/niveles.hpp"

int main() {
    sf::RenderWindow ventana(sf::VideoMode({640, 640}), "Sokoban");
    ventana.setFramerateLimit(60);

    Mapa mapa;
    Niveles niveles;
    Jugador jugador;

    int nivelActual = 0;
    mapa.cargarNivel(niveles.getNivel(nivelActual), jugador);

    while (ventana.isOpen()) {
        while (const std::optional event = ventana.pollEvent()) {
            
            if (event->is<sf::Event::Closed>()) {
                ventana.close();
            }

            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                
                int dx = 0;
                int dy = 0;

                if (keyPressed->code == sf::Keyboard::Key::Right || keyPressed->code == sf::Keyboard::Key::D) dx = 1;
                else if (keyPressed->code == sf::Keyboard::Key::Left || keyPressed->code == sf::Keyboard::Key::A) dx = -1;
                else if (keyPressed->code == sf::Keyboard::Key::Up || keyPressed->code == sf::Keyboard::Key::W) dy = -1;
                else if (keyPressed->code == sf::Keyboard::Key::Down || keyPressed->code == sf::Keyboard::Key::S) dy = 1;

                if (dx != 0 || dy != 0) {
                    
                    int xActual = (int)(jugador.getPosInicial().x / 32); 
                    int yActual = (int)(jugador.getPosInicial().y / 32);

                    //miro el destino de adelante pa
                    int tileDestino = mapa.getTile(xActual + dx, yActual + dy);

                    bool puedoMoverme = false;

                    // Caso 1 , camino libre (aura)
                    if (tileDestino == 0) {
                        puedoMoverme = true;
                    }

                   // CASO 2, intento eempujar
                    else if (tileDestino == 3 || tileDestino == 5) {
                        
                        // Miro dos pasos adelante (atras de la caja)
                        int tileTrasCaja = mapa.getTile(xActual + dx * 2, yActual + dy * 2);
                        if (tileTrasCaja == 0 || tileTrasCaja == 4) {

                            //Si muevo un 3 (Caja normal), estaba en el piso -> Dejo un 0
                            //Si muevo un 5 (Caja verde), estaba en la meta -> Dejo un 4 (El punto rojo)
                            int loQueDejo = (tileDestino == 3) ? 0 : 4;
                            mapa.setTile(xActual + dx, yActual + dy, loQueDejo);

                            //A donde va la caja ahora te preguntaras Kevincito
                            //Si va al piso (0) -> Se vuelve caja normal (3)
                            //Si va a la meta (4) -> Se vuelve caja verde (5) osea, WIN
                            int loQuePongo = (tileTrasCaja == 0) ? 3 : 5;
                            mapa.setTile(xActual + dx * 2, yActual + dy * 2, loQuePongo);
                            
                            puedoMoverme = true;
                        }
                    }
                    if (puedoMoverme) {
                        jugador.mover(dx * 32.f, dy * 32.f);
                        
                        sf::Vector2f nuevaPos = jugador.getPosInicial();
                        nuevaPos.x += dx * 32.f;
                        nuevaPos.y += dy * 32.f;
                        jugador.setPosInicial(nuevaPos);

                        // Debug en título, porq no me detectaba teclas
                        ventana.setTitle("Sokoban - Moviendo...");
                    } else {
                        ventana.setTitle("Sokoban - Bloqueado!");
                    }
                }
            }
        }

        ventana.clear();
        mapa.renderizar(ventana);
        jugador.renderizar(ventana);
        ventana.display();
    }

    return 0;
}