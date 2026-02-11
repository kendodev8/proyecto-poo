#include <cstdio>
#include <iostream>
#include "../include/mapa.hpp"

Mapa::Mapa(){
    cargarTexturas();
}

void Mapa::cargarNivel(const grillaNivel& nivel, Jugador& jugador){
    botonesNecesarios = 0;
    
    for(int y = 0; y < ALTO_MAX; y++){
        for(int x = 0; x < ANCHO_MAX; x++){
            grillaMapa[y][x] = nivel[y][x];

            if(grillaMapa[y][x] == 9){
                jugador.setPos({x * TAMAÑO_TILE, y * TAMAÑO_TILE});
                grillaMapa[y][x] = PISO;
            }

            if(grillaMapa[y][x] == BOTON || grillaMapa[y][x] == CAJAOBJETIVO){
                botonesNecesarios++;
            }
        }
    }
}

bool Mapa::cargarTexturas(){
    sf::Texture textura;

    if(!textura.loadFromFile("./assets/piso.png")){
        std::cerr << "Error cargando piso.png" << std::endl;
        return false;
    }
    texturas[PISO] = textura;

    if(!textura.loadFromFile("./assets/pared.png")){
        std::cerr << "Error cargando pared.png" << std::endl;
        return false;
    }
    texturas[PARED] = textura;

    if(!textura.loadFromFile("./assets/caja.png")){
        std::cerr << "Error cargando caja.png" << std::endl;
        return false;
    }
    texturas[CAJA] = textura;

    if(!textura.loadFromFile("./assets/cajaobjetivo.png")){
        std::cerr << "Error cargando cajaobjetivo.png" << std::endl;
        return false;
    }
    texturas[CAJAOBJETIVO] = textura;

    if(!textura.loadFromFile("./assets/boton.png")){
        std::cerr << "Error cargando boton.png" << std::endl;
        return false;
    }
    texturas[BOTON] = textura;

    return true;
}

void Mapa::renderizar(sf::RenderWindow& ventana){
    for(int y = 0; y < ALTO_MAX; y++){
        for(int x = 0; x < ANCHO_MAX; x++){
            float posX = x * TAMAÑO_TILE;
            float posY = y * TAMAÑO_TILE;
            int tipo = grillaMapa[y][x];

            sf::Sprite spritePiso(texturas[PISO]);
            spritePiso.setPosition({posX, posY});
            ventana.draw(spritePiso);

            switch(tipo){
                case PARED: {
                    sf::Sprite spritePared(texturas[PARED]);
                    spritePared.setPosition({posX, posY});
                    ventana.draw(spritePared);
                    break;
                }

                case CAJA: {
                    sf::Sprite spriteCaja(texturas[CAJA]);
                    spriteCaja.setPosition({posX, posY});
                    ventana.draw(spriteCaja);
                    break;
                }

                case CAJAOBJETIVO: {
                    sf::Sprite spriteCajaObj(texturas[CAJAOBJETIVO]);
                    spriteCajaObj.setPosition({posX, posY});
                    ventana.draw(spriteCajaObj);
                    break;
                }

                case BOTON: {
                    sf::Sprite spriteBoton(texturas[BOTON]);
                    spriteBoton.setPosition({posX, posY});
                    ventana.draw(spriteBoton);
                    break;
                }
            }
        }
    }
}

int Mapa::getTile(int x, int y){
    if(x < 0 || x >= ANCHO_MAX || y < 0 || y >= ALTO_MAX){
        return 1;
    }
    return grillaMapa[y][x];
}

void Mapa::setTile(int x, int y, int valor){
    if(x >= 0 && x < ANCHO_MAX && y >= 0 && y < ALTO_MAX){
        grillaMapa[y][x] = valor;
    }
}

void Mapa::chequearBotones(){
    botonesPresionados = 0;

    for(int y = 0; y < ALTO_MAX; y++){
        for(int x = 0; x < ANCHO_MAX; x++){
            if(grillaMapa[y][x] == 5){
                botonesPresionados++;
            }
        }
    }
}

bool Mapa::nivelCompletado(){
    return botonesPresionados == botonesNecesarios;
}