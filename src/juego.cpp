#include "../include/juego.hpp"

Juego::Juego() : 
    ventana(sf::VideoMode({640, 480}), "Sokoban")
{
    ventana.setFramerateLimit(30);
    nivelActual = 0;
    mapa.cargarNivel(niveles.getNivel(nivelActual), jugador);
}

void Juego::run(){
    while(ventana.isOpen()){
        actualizar();
        renderizar();
    }
}

void Juego::actualizar(){
    manejarInput();
    mapa.chequearBotones();

    if(mapa.nivelCompletado()){
        nivelActual++;
        mapa.cargarNivel(niveles.getNivel(nivelActual), jugador);
    }
}

void Juego::renderizar(){
    ventana.clear(sf::Color(40, 40, 40));
    mapa.renderizar(ventana);
    jugador.renderizar(ventana);
    ventana.display();
}

void Juego::manejarInput(){
    while(const std::optional evento = ventana.pollEvent()){
        if(evento->is<sf::Event::Closed>()){
            ventana.close();
        }

        if(const auto* teclaPresionada = evento->getIf<sf::Event::KeyPressed>()){
            int dx = 0;
            int dy = 0;

            if(teclaPresionada->code == sf::Keyboard::Key::Right || teclaPresionada->code == sf::Keyboard::Key::D) dx = 1;
            else if(teclaPresionada->code == sf::Keyboard::Key::Left || teclaPresionada->code == sf::Keyboard::Key::A) dx = -1;
            else if(teclaPresionada->code == sf::Keyboard::Key::Up || teclaPresionada->code == sf::Keyboard::Key::W) dy = -1;
            else if(teclaPresionada->code == sf::Keyboard::Key::Down || teclaPresionada->code == sf::Keyboard::Key::S) dy = 1;

            if(dx != 0 || dy != 0){
                int xActual = (int)(jugador.getPos().x / TAMAÑO_TILE);
                int yActual = (int)(jugador.getPos().y / TAMAÑO_TILE);

                int tileDestino = mapa.getTile(xActual + dx, yActual + dy);

                bool puedoMoverme = false;

                if(tileDestino == PISO || tileDestino == BOTON){
                    puedoMoverme = true;
                }

                if(tileDestino == CAJA || tileDestino == CAJAOBJETIVO){
                    // Mirar dos pasos adelante (atras de la caja)
                    int tileTrasCaja = mapa.getTile(xActual + dx * 2, yActual + dy * 2);

                    if(tileTrasCaja == PISO || tileTrasCaja == BOTON){
                        //Si muevo un 3 (Caja normal), estaba en el piso -> Dejo un 0 (piso)
                        //Si muevo un 5 (Caja verde), estaba en la meta -> Dejo un 4 (punto rojo)
                        int tileViejo = (tileDestino == CAJA) ? PISO : BOTON;
                        mapa.setTile(xActual + dx, yActual + dy, tileViejo);

                        //Si va al piso (0) -> Se vuelve caja normal (3)
                        //Si va a la meta (4) -> Se vuelve caja verde (5)
                        int tileNuevo = (tileTrasCaja == PISO) ? CAJA : CAJAOBJETIVO; 
                        mapa.setTile(xActual + dx * 2, yActual + dy * 2, tileNuevo);
                            
                        puedoMoverme = true;
                    }
                }

                if(puedoMoverme){
                        sf::Vector2f nuevaPos = jugador.getPos();
                        nuevaPos.x += dx * 32.f;
                        nuevaPos.y += dy * 32.f;
                        jugador.setPos(nuevaPos);
                }
            }

            if (teclaPresionada->code == sf::Keyboard::Key::R) mapa.cargarNivel(niveles.getNivel(nivelActual), jugador);
        }
    }
}