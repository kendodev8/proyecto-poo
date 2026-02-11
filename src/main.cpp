#include "../include/juego.hpp"

int main() {
    Juego juego;
    juego.run();
    return 0;
    /*sf::RenderWindow ventana(sf::VideoMode({640, 640}), "Sokoban");
    ventana.setFramerateLimit(30);

    Mapa mapa;
    Niveles niveles;
    Jugador jugador;

    int nivelActual = 0;
    int condicionesVictoria = 0;
    mapa.cargarNivel(niveles.getNivel(nivelActual), jugador);

    while (ventana.isOpen()) {
        while(const std::optional event = ventana.pollEvent()){
            
            if(event->is<sf::Event::Closed>()){
                ventana.close();
            }

            if(const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()){
                int dx = 0;
                int dy = 0;

                if (keyPressed->code == sf::Keyboard::Key::Right || keyPressed->code == sf::Keyboard::Key::D) dx = 1;
                else if (keyPressed->code == sf::Keyboard::Key::Left || keyPressed->code == sf::Keyboard::Key::A) dx = -1;
                else if (keyPressed->code == sf::Keyboard::Key::Up || keyPressed->code == sf::Keyboard::Key::W) dy = -1;
                else if (keyPressed->code == sf::Keyboard::Key::Down || keyPressed->code == sf::Keyboard::Key::S) dy = 1;

                if(dx != 0 || dy != 0){
                    int xActual = (int)(jugador.getPosInicial().x / 32);
                    int yActual = (int)(jugador.getPosInicial().y / 32);

                    // Chequear direccion destino
                    int tileDestino = mapa.getTile(xActual + dx, yActual + dy);

                    bool puedoMoverme = false;

                    // Camino libre
                    if (tileDestino == 0 || tileDestino == 4) {
                        puedoMoverme = true;
                    }

                   // Intentar empujar caja
                    else if (tileDestino == 3 || tileDestino == 5) {
                        // Mirar dos pasos adelante (atras de la caja)
                        int tileTrasCaja = mapa.getTile(xActual + dx * 2, yActual + dy * 2);
                        if(tileTrasCaja == 0 || tileTrasCaja == 4){
                            //Si muevo un 3 (Caja normal), estaba en el piso -> Dejo un 0 (piso)
                            //Si muevo un 5 (Caja verde), estaba en la meta -> Dejo un 4 (punto rojo)
                            int tileViejo = (tileDestino == 3) ? 0 : 4;
                            mapa.setTile(xActual + dx, yActual + dy, tileViejo);

                            //Si va al piso (0) -> Se vuelve caja normal (3)
                            //Si va a la meta (4) -> Se vuelve caja verde (5)
                            int tileNuevo = (tileTrasCaja == 0) ? 3 : 5;
                            if(tileNuevo == 5){
                                condicionesVictoria++;
                            }
                            mapa.setTile(xActual + dx * 2, yActual + dy * 2, tileNuevo);
                            
                            puedoMoverme = true;
                        }
                    }
                    if(puedoMoverme){
                        jugador.mover(dx * 32.f, dy * 32.f);
                        
                        sf::Vector2f nuevaPos = jugador.getPosInicial();
                        nuevaPos.x += dx * 32.f;
                        nuevaPos.y += dy * 32.f;
                        jugador.setPosInicial(nuevaPos);

                        // Debug en título
                        ventana.setTitle("Sokoban - Moviendo...");
                    } else {
                        ventana.setTitle("Sokoban - Bloqueado!");
                    }
                }

                if(keyPressed->code == sf::Keyboard::Key::R) mapa.cargarNivel(niveles.getNivel(nivelActual), jugador);
            }
        }

        if(condicionesVictoria == 3){
            nivelActual++;
            mapa.cargarNivel(niveles.getNivel(nivelActual), jugador);
            condicionesVictoria = 0;
        }

        ventana.clear();
        mapa.renderizar(ventana);
        jugador.renderizar(ventana);
        ventana.display();
    }

    return 0;*/
}