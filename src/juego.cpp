#include "../include/juego.hpp"

Juego::Juego() : 
    ventana(sf::VideoMode({384, 384}), "Sokoban"),
    fuente("./assets/fuente.ttf"),
    textoVictoria(fuente)
{
    ventana.setFramerateLimit(30);

    //carpgo AUDIO
    if(musicaFondo.openFromFile("./assets/musica1.mp3")){
        musicaFondo.setLooping(true); 
        musicaFondo.setVolume(50.f); 
        musicaFondo.play();
    }
    if(bufferMovimiento.loadFromFile("./assets/movimiento.mp3")){
        sonidoMovimiento.emplace(bufferMovimiento);
        sonidoMovimiento->setVolume(100.f);
    }

    if(bufferSiguiente.loadFromFile("./assets/siguiente.mp3")){
        sonidoSiguiente.emplace(bufferSiguiente);
    }
    if(bufferVictoria.loadFromFile("./assets/victoria.mp3")){
        sonidoVictoria.emplace(bufferVictoria);
    }

    //pantalla y texto
    pantallaActual = Pantalla::JUGANDO; // Arrancamos jugando
    
    textoVictoria.setString("¡FELICITACIONES!\nPasaste todo el juego.\n\n(Pronto habra un menu aqui)");
    textoVictoria.setCharacterSize(24);
    textoVictoria.setFillColor(sf::Color::White);
    textoVictoria.setPosition({30.f, 150.f});

    nivelActual = 6;
    mapa.cargarNivel(niveles.getNivel(nivelActual), jugador);
}

void Juego::run(){
    while(ventana.isOpen()){
        actualizar();
        renderizar();
    }
}

void Juego::actualizar(){
    // SOLO reviso las cajas y el movimiento si estamos jugando
    manejarInput();
    if (pantallaActual == Pantalla::JUGANDO) {
        
        mapa.chequearBotones();

        if(mapa.nivelCompletado()){
            nivelActual++;
            
            // Si todavía hay niveles, pal el sig
            if(nivelActual < niveles.getCantidad()){
                if(sonidoSiguiente) sonidoSiguiente->play();
                mapa.cargarNivel(niveles.getNivel(nivelActual), jugador);
                historial.clear();
            } else {
            // Si ganan, toca el sonido UNA SOLA VEZ y cambia la pantalla, 
            // no sabes el quilombo que tenia con esto
                if(sonidoVictoria) sonidoVictoria->play();
                pantallaActual = Pantalla::VICTORIA;
            }
        }
        
    }
    // Si la pantallaActual es VICTORIA, el juego ignora todo lo de arriba 
    // y se queda tranquilo mostrando el texto
}

void Juego::renderizar(){
    ventana.clear();

    if (pantallaActual == Pantalla::JUGANDO) {
        mapa.renderizar(ventana);
        jugador.renderizar(ventana);
    } 
    else if (pantallaActual == Pantalla::VICTORIA) {
        ventana.draw(textoVictoria); // Pantalla negra con texto por ahora
    }

    ventana.display();
}

void Juego::manejarInput(){
    while(const std::optional evento = ventana.pollEvent()){

        if(evento->is<sf::Event::Closed>()){
            ventana.close();
        }

        if(const auto* teclaPresionada = evento->getIf<sf::Event::KeyPressed>()){
            
            //habilito teclas solo si juego
            if (pantallaActual == Pantalla::JUGANDO) {
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
            //Si estoyen la VICTORIA y toco ESCAPE, cierro a la bosta , pora hora 
            else if (pantallaActual == Pantalla::VICTORIA) {
                if(teclaPresionada->code == sf::Keyboard::Key::Escape){
                    ventana.close();
                }
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

        //sonido de pizadas copadas
        if(sonidoMovimiento){sonidoMovimiento->play();}

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