#pragma once

#include <SFML/Graphics.hpp>
#include <cstdio>

class Entidad {
    public:
        virtual ~Entidad() = default;

        void setPos(sf::Vector2f pos){
            printf("Pos X: %f\n", pos.x); //herramienta de debug, para verificar que se están recibiendo las coordenadas correctas
            printf("Pos Y: %f\n", pos.y);
            posInicial = pos;
            printf("Pos X: %f\n", posInicial.x);
            printf("Pos Y: %f\n", posInicial.y);
        }

        sf::Vector2f getPos(){
            return posInicial;
        }

    protected:
        sf::Vector2f posInicial;

};

//Este archivo define la clase padre Entidad, aplica encapsulamiento mediante getters y setters para la posición, usa protected para 
//facilitar la herencia a las clases hijas, y un destructor virtual por default para asegurar una buena gestión de memoria en caso de usar polimorfismo