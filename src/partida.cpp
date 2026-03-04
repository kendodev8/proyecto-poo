#include "../include/partida.hpp"
#include "../include/juego.hpp"
#include "../include/opciones.hpp"
#include "../include/victoria.hpp"
#include <cstring>

Partida::Partida() :
    fuente("./assets/fuente.ttf"),
    textoMovimientos(fuente),
    textoNivel(fuente)
{
    textoMovimientos.setString("MOVIMIENTOS: 0");
    textoMovimientos.setPosition({5.f, 10.f});
    textoMovimientos.setCharacterSize(20);
    textoMovimientos.setFillColor(sf::Color::White);
    textoMovimientos.setOutlineColor(sf::Color::Black);
    textoMovimientos.setOutlineThickness(1.f);

    textoNivel.setString("NIVEL: 1");
    textoNivel.setPosition({190.f, 10.f});
    textoNivel.setCharacterSize(20);
    textoNivel.setFillColor(sf::Color::White);
    textoNivel.setOutlineColor(sf::Color::Black);
    textoNivel.setOutlineThickness(1.f);

    movimientos = 0;
    nivelActual = 0;
    mapa.cargarNivel(niveles.getNivel(nivelActual), jugador);
}

void Partida::renderizar(sf::RenderWindow &ventana){
    mapa.renderizar(ventana);
    jugador.renderizar(ventana);
    ventana.draw(textoMovimientos);
    ventana.draw(textoNivel);
}

void Partida::actualizar(Juego &juego){
    mapa.chequearBotones();

    textoMovimientos.setString("MOVIMIENTOS: " + std::to_string(movimientos));
    textoNivel.setString("NIVEL: " + std::to_string(nivelActual + 1));

    if(mapa.nivelCompletado()){
        juego.setRegistroScores(nivelActual, movimientos, juego.getNombreJugador());
        nivelActual++;
        movimientos = 0;
        
        if(nivelActual < niveles.getCantidad()){
            mapa.cargarNivel(niveles.getNivel(nivelActual), jugador);
        } else {
            juego.cambiarEscena(new Victoria());
        }
    }
}

void Partida::procesarEvento(Juego &juego, const sf::Event &evento){
    if(const auto* teclaPresionada = evento.getIf<sf::Event::KeyPressed>()){
        int dx = 0, dy = 0;
        if(teclaPresionada->code == sf::Keyboard::Key::Right || teclaPresionada->code == sf::Keyboard::Key::D) dx = 1;
        else if(teclaPresionada->code == sf::Keyboard::Key::Left || teclaPresionada->code == sf::Keyboard::Key::A) dx = -1;
        else if(teclaPresionada->code == sf::Keyboard::Key::Up || teclaPresionada->code == sf::Keyboard::Key::W) dy = -1;
        else if(teclaPresionada->code == sf::Keyboard::Key::Down || teclaPresionada->code == sf::Keyboard::Key::S) dy = 1;

        if(dx != 0 || dy != 0) intentarMover(dx, dy);

        if(teclaPresionada->code == sf::Keyboard::Key::R){
            mapa.cargarNivel(niveles.getNivel(nivelActual), jugador);
            historial.clear();
            movimientos = 0;
        }

        if(teclaPresionada->code == sf::Keyboard::Key::Z) deshacerMovimiento();

        if(teclaPresionada->code == sf::Keyboard::Key::Escape){
            juego.pausarJuego(new Opciones(false));
        }
    }
}

void Partida::intentarMover(const int &dx, const int &dy){
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
        movimientos++;

        //if(sonidoMovimiento){sonidoMovimiento->play();}

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

void Partida::guardarEstado(){
    Estado estado;

    estado.posicionJugador = jugador.getPos();
    estado.copiaGrilla = mapa.getGrilla();

    historial.push_back(estado);
}

void Partida::deshacerMovimiento(){
    if(historial.empty()) return;

    movimientos--;

    Estado ultimoEstado = historial.back();

    jugador.setPos(ultimoEstado.posicionJugador);

    mapa.setGrilla(ultimoEstado.copiaGrilla);
    
    historial.pop_back();
}