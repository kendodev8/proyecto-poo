#include "../include/juego.hpp"

Juego::Juego() : 
    ventana(sf::VideoMode({384, 384}), "Sokoban"),
    fuente("./assets/fuente.ttf")
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
        historial.clear();
    }
}

void Juego::renderizar(){
    ventana.clear();
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
                intentarMover(dx, dy);
            }

            if(teclaPresionada->code == sf::Keyboard::Key::R){
                mapa.cargarNivel(niveles.getNivel(nivelActual), jugador);
                historial.clear();
            }

            if(teclaPresionada->code == sf::Keyboard::Key::Z){
                deshacerMovimiento();
            }
        }
    }
}

void Juego::intentarMover(int dx, int dy){
    sf::Vector2f posActual = jugador.getPos();
    int xActual = (int)(posActual.x / TAMAÑO_TILE);
    int yActual = (int)(posActual.y / TAMAÑO_TILE);

    int tileDestino = mapa.getTile(xActual + dx, yActual + dy);

    bool empujeValido = false;

    if(tileDestino == CAJA || tileDestino == CAJAOBJETIVO){
        int tileTrasCaja = mapa.getTile(xActual + dx * 2, yActual + dy * 2);

        if(tileTrasCaja == PISO || tileTrasCaja == BOTON){
            empujeValido = true;
        }
    }

    if(tileDestino == PISO || tileDestino == BOTON || empujeValido){
        guardarEstado();

        if(empujeValido){
            //Si muevo un 3 (Caja normal), estaba en el piso -> Dejo un 0 (piso)
            //Si muevo un 5 (Caja verde), estaba en la meta -> Dejo un 4 (punto rojo)
            int tileViejo = (tileDestino == CAJA) ? PISO : BOTON;
            mapa.setTile(xActual + dx, yActual + dy, tileViejo);

            //Si va al piso (0) -> Se vuelve caja normal (3)
            //Si va al boton (4) -> Se vuelve caja verde (5)
            int tileNuevo = (mapa.getTile(xActual + dx * 2, yActual + dy * 2) == PISO) ? CAJA : CAJAOBJETIVO;
            mapa.setTile(xActual + dx * 2, yActual + dy * 2, tileNuevo);
        }

        sf::Vector2f nuevaPos = posActual;
        nuevaPos.x += dx * 32.f;
        nuevaPos.y += dy * 32.f;
        jugador.setPos(nuevaPos);
    }
}

void Juego::guardarEstado(){
    Estado estado;

    estado.posicionJugador = jugador.getPos();
    estado.copiaGrilla = mapa.getGrilla();

    historial.push_back(estado);
}

void Juego::deshacerMovimiento(){
    if(historial.empty()) return;

    Estado ultimoEstado = historial.back();

    jugador.setPos(ultimoEstado.posicionJugador);

    mapa.setGrilla(ultimoEstado.copiaGrilla);
    
    historial.pop_back();
}