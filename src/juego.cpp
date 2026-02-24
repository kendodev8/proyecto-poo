#include "../include/juego.hpp"

Juego::Juego() : 
    ventana(sf::VideoMode({384, 384}), "Sokoban"),
    fuente("./assets/fuente.ttf"),
    textoVictoria(fuente),
    textoJugar(fuente),
    textoOpciones(fuente),
    textoVolver(fuente),
    textoVolumen(fuente),
    spriteFondoMenu(texturaFondoMenu), 
    botonJugar(texturaUI),
    botonOpciones(texturaUI),
    botonVolver(texturaUI),
    perillaVolumen(texturaUI),
    spriteAjustes(texturaAjustes),
    textoSalir(fuente)
{
    ventana.setFramerateLimit(30);

    //CARGAR AUDIO
    if(bufferSelect.loadFromFile("./assets/select.mp3")){
        sonidoSelect.emplace(bufferSelect);
    }

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

    //CARGAR GRÁFICOS DEL MENÚ
    pantallaActual = Pantalla::MENU; 
    pantallaAnterior = Pantalla::MENU;

    if (texturaFondoMenu.loadFromFile("./assets/menu_fondo.png")) {
        spriteFondoMenu.setTexture(texturaFondoMenu,true); 
        sf::Vector2u tam = texturaFondoMenu.getSize();
        spriteFondoMenu.setScale({384.f / tam.x, 384.f / tam.y});
    }

    if (texturaAjustes.loadFromFile("./assets/icono_ajustes.png")) {
        spriteAjustes.setTexture(texturaAjustes,true);
        spriteAjustes.setPosition({345.f, 5.f}); 
        spriteAjustes.setScale({0.02f, 0.02f}); 
    }

    //UI
    if (texturaUI.loadFromFile("./assets/ui_cuadrado.png")) {
        botonJugar.setTexture(texturaUI, true);
        botonJugar.setPosition({115.f, 100.f});
        botonJugar.setScale({3.0f, 1.3f}); 

        botonOpciones.setTexture(texturaUI, true); 
        botonOpciones.setPosition({115.f, 180.f});
        botonOpciones.setScale({3.0f, 1.3f});

        botonVolver.setTexture(texturaUI, true); 
        botonVolver.setPosition({115.f, 300.f});
        botonVolver.setScale({3.0f, 1.3f});

        perillaVolumen.setTexture(texturaUI, true); 
        perillaVolumen.setPosition({170.f, 185.f}); 
        perillaVolumen.setScale({0.10f, 0.8f}); 
    }

    //TEXTOS
    textoJugar.setString("JUGAR");
    textoJugar.setCharacterSize(30); 
    textoJugar.setFillColor(sf::Color::White);
    textoJugar.setOutlineColor(sf::Color::Black); 
    textoJugar.setOutlineThickness(4.f); 
    textoJugar.setPosition({145.f, 160.f}); 

    textoSalir.setString("MENU PRINCIPAL");
    textoSalir.setCharacterSize(22); 
    textoSalir.setFillColor(sf::Color::White);
    textoSalir.setOutlineColor(sf::Color::Black);
    textoSalir.setOutlineThickness(4.f);
    textoSalir.setPosition({105.f, 260.f}); // Centrado en los ladrillos

    textoOpciones.setString("VOLUMEN");
    textoOpciones.setCharacterSize(26);
    textoOpciones.setFillColor(sf::Color::White);
    textoOpciones.setOutlineColor(sf::Color::Black);
    textoOpciones.setOutlineThickness(4.f);
    textoOpciones.setPosition({135.f, 220.f}); 

    textoVolver.setString("VOLVER");
    textoVolver.setCharacterSize(22);
    textoVolver.setFillColor(sf::Color::White);
    textoVolver.setOutlineColor(sf::Color::Black);
    textoVolver.setOutlineThickness(4.f);
    textoVolver.setPosition({145.f, 230.f}); 

    textoVolumen.setString("Volumen: 5");
    textoVolumen.setCharacterSize(22); 
    textoVolumen.setFillColor(sf::Color::Black); 
    textoVolumen.setOutlineColor(sf::Color::White); 
    textoVolumen.setOutlineThickness(2.f);
    textoVolumen.setPosition({138.f, 150.f}); 

    //barra (Gris)
    barraVolumenFondo.setFillColor(sf::Color(100, 100, 100));
    barraVolumenFondo.setSize({140.f, 10.f});
    barraVolumenFondo.setPosition({122.f, 210.f});
    perillaVolumen.setPosition({192.f, 195.f});

    opcionSeleccionada = 0; // Arranca brillando "JUGAR"
    nivelVolumen = 5;       // Volumen a la mitad (nivel 5)

    //TEXTO VICTORIA Y CARGA DE NIVEL, agradece que te ordeno todo
    textoVictoria.setString("¡FELICITACIONES!\nPasaste todo el juego.\n\n(hasta que haya menu)");
    textoVictoria.setCharacterSize(24);
    textoVictoria.setFillColor(sf::Color::White);
    textoVictoria.setPosition({30.f, 150.f});

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

    if (pantallaActual == Pantalla::MENU) {
        ventana.draw(spriteFondoMenu);
       // ventana.draw(botonJugar);
        ventana.draw(textoJugar);
        //ventana.draw(botonOpciones);
        ventana.draw(textoOpciones);
    }
    else if (pantallaActual == Pantalla::OPCIONES) {
        ventana.draw(spriteFondoMenu);
        ventana.draw(textoVolumen);
        ventana.draw(barraVolumenFondo);
        ventana.draw(perillaVolumen);
        //ventana.draw(botonVolver);
        ventana.draw(textoVolver);
        ventana.draw(textoSalir);
    }
    else if (pantallaActual == Pantalla::JUGANDO) {
        mapa.renderizar(ventana);
        jugador.renderizar(ventana);
    } 
    else if (pantallaActual == Pantalla::VICTORIA) {
        ventana.draw(textoVictoria);
    }

    ventana.display();
}

void Juego::manejarInput(){
    while(const std::optional evento = ventana.pollEvent()){
        
        if(evento->is<sf::Event::Closed>()){
            ventana.close();
        }

        if(const auto* teclaPresionada = evento->getIf<sf::Event::KeyPressed>()){
            
            //MENÚ PRINCIPAL
            if (pantallaActual == Pantalla::MENU) {
                if(teclaPresionada->code == sf::Keyboard::Key::Up || teclaPresionada->code == sf::Keyboard::Key::W){
                    opcionSeleccionada = 0; 
                    if(sonidoSelect) sonidoSelect->play();
                }
                else if(teclaPresionada->code == sf::Keyboard::Key::Down || teclaPresionada->code == sf::Keyboard::Key::S){
                    opcionSeleccionada = 1; 
                    if(sonidoSelect) sonidoSelect->play();
                }
                else if(teclaPresionada->code == sf::Keyboard::Key::Enter){
                    if(opcionSeleccionada == 0) {
                        pantallaActual = Pantalla::JUGANDO;
                        pantallaAnterior = Pantalla::MENU;
                    }
                    else if(opcionSeleccionada == 1) {
                        pantallaActual = Pantalla::OPCIONES;
                        pantallaAnterior = Pantalla::MENU;
                        opcionSeleccionada = 0;
                    }
                }
            }
            //OPCIONES (PAUSA)
            else if (pantallaActual == Pantalla::OPCIONES) {
                
                if(teclaPresionada->code == sf::Keyboard::Key::Up || teclaPresionada->code == sf::Keyboard::Key::W){
                    if(opcionSeleccionada > 0) {
                        opcionSeleccionada--;
                        if(sonidoSelect) sonidoSelect->play();
                    }
                }
                else if(teclaPresionada->code == sf::Keyboard::Key::Down || teclaPresionada->code == sf::Keyboard::Key::S){
                    if(opcionSeleccionada < 2) { // 0: Barra, 1: Volver, 2: Salir
                        opcionSeleccionada++;
                        if(sonidoSelect) sonidoSelect->play();
                    }
                }

                //JUSTAR VOLUMEN
                if (opcionSeleccionada == 0) {
                    if(teclaPresionada->code == sf::Keyboard::Key::Left || teclaPresionada->code == sf::Keyboard::Key::A){
                        if(nivelVolumen > 0) {
                            nivelVolumen--; 
                        }
                    }
                    else if(teclaPresionada->code == sf::Keyboard::Key::Right || teclaPresionada->code == sf::Keyboard::Key::D){
                        if(nivelVolumen < 10) {
                            nivelVolumen++;
                        }
                    }
                }
                //ENTER
                else if(teclaPresionada->code == sf::Keyboard::Key::Enter){
                    if(opcionSeleccionada == 1) { 
                        pantallaActual = pantallaAnterior; 
                    }
                    else if(opcionSeleccionada == 2) { 
                        nivelActual = 0; 
                        mapa.cargarNivel(niveles.getNivel(nivelActual), jugador);
                        historial.clear();
                        
                        pantallaActual = Pantalla::MENU;
                        opcionSeleccionada = 0; 
                    }
                }

                //ACTUALIZACIÓN GRÁFICA Y DE AUDIO
                float porcentaje = nivelVolumen * 10.f;
                musicaFondo.setVolume(porcentaje);
                if(sonidoMovimiento) sonidoMovimiento->setVolume(porcentaje);
                
                textoVolumen.setString("Volumen: " + std::to_string(nivelVolumen));
                perillaVolumen.setPosition({125.f + (nivelVolumen * 14.f), 195.f});
            }
            //CONTROLES: JUGANDO
            else if (pantallaActual == Pantalla::JUGANDO) {
                int dx = 0, dy = 0;
                if(teclaPresionada->code == sf::Keyboard::Key::Right || teclaPresionada->code == sf::Keyboard::Key::D) dx = 1;
                else if(teclaPresionada->code == sf::Keyboard::Key::Left || teclaPresionada->code == sf::Keyboard::Key::A) dx = -1;
                else if(teclaPresionada->code == sf::Keyboard::Key::Up || teclaPresionada->code == sf::Keyboard::Key::W) dy = -1;
                else if(teclaPresionada->code == sf::Keyboard::Key::Down || teclaPresionada->code == sf::Keyboard::Key::S) dy = 1;

                if(dx != 0 || dy != 0) intentarMover(dx, dy);

                if(teclaPresionada->code == sf::Keyboard::Key::R){
                    mapa.cargarNivel(niveles.getNivel(nivelActual), jugador);
                    historial.clear();
                }
                if(teclaPresionada->code == sf::Keyboard::Key::Z) deshacerMovimiento();
                
                // Con Escape abrplas opciones desde el juego
                if(teclaPresionada->code == sf::Keyboard::Key::Escape){
                    pantallaActual = Pantalla::OPCIONES;
                    opcionSeleccionada = 0; // Entro con el volumen seleccionado
                }
            }
            else if (pantallaActual == Pantalla::VICTORIA) {
                if(teclaPresionada->code == sf::Keyboard::Key::Escape) ventana.close();
            }
        }
    }

   //efectos visuales
    textoJugar.setFillColor(sf::Color::White);
    textoOpciones.setFillColor(sf::Color::White);
    textoVolver.setFillColor(sf::Color::White);
    textoVolumen.setFillColor(sf::Color::Black); 

    if (pantallaActual == Pantalla::MENU) {
        if(opcionSeleccionada == 0) textoJugar.setFillColor(sf::Color::Yellow);
        if(opcionSeleccionada == 1) textoOpciones.setFillColor(sf::Color::Yellow);
    } 
    else if (pantallaActual == Pantalla::OPCIONES) {
        textoVolumen.setFillColor(sf::Color::Black); 
        textoVolver.setFillColor(sf::Color::White);
        textoSalir.setFillColor(sf::Color::White);

        if(opcionSeleccionada == 0) textoVolumen.setFillColor(sf::Color(80, 80, 80));
        if(opcionSeleccionada == 1) textoVolver.setFillColor(sf::Color::Yellow);
        if(opcionSeleccionada == 2) textoSalir.setFillColor(sf::Color::Yellow); // <-- ¡Ahora sí va a brillar!
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