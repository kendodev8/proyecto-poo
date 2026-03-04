#include "../include/juego.hpp"

Juego::Juego(Escena *primerEscena) : 
    ventana(sf::VideoMode({384, 384}), "Sokoban"),
    escena(primerEscena)
{
    ventana.setFramerateLimit(30);

    /*CARGAR AUDIO
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
    }*/
}

void Juego::run(){
    while(ventana.isOpen()){
        while(const std::optional evento = ventana.pollEvent()){
            if(evento->is<sf::Event::Closed>()){
                ventana.close();
            }

            escena->procesarEvento(*this, *evento);
        }

        escena->actualizar(*this);
        
        ventana.clear();
        escena->renderizar(ventana);
        ventana.display();

    if (siguiente != nullptr) {
        if (pausando) {
        escenaPausada = escena; 
        escena = siguiente; 
        pausando = false;
        siguiente = nullptr;
        continue; 
    }
    if (escena != nullptr) {
        delete escena;
    }
    escena = siguiente;
    siguiente = nullptr;
}
    }
}

Juego::~Juego(){
    delete escena;
}

void Juego::cambiarEscena(Escena * siguienteEscena){
    siguiente = siguienteEscena;
}

void Juego::pausarJuego(Escena* menuPausa) {
    this->pausando = true;
    this->siguiente = menuPausa;
}

void Juego::reanudarJuego() {
    if (this->escenaPausada != nullptr) {
        this->siguiente = this->escenaPausada;
        this->escenaPausada = nullptr;
    }
}