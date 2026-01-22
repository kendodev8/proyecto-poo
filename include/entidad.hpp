#pragma once

#include <SFML/Graphics.hpp>
#include <cstdio>

class Entidad {
    public:
        virtual ~Entidad() = default;

        void setPosInicial(sf::Vector2f pos){
            printf("Pos X: %f\n", pos.x);
            printf("Pos Y: %f\n", pos.y);
            posInicial = pos;
            printf("Pos X: %f\n", posInicial.x);
            printf("Pos Y: %f\n", posInicial.y);
        }

        sf::Vector2f getPosInicial(){
            return posInicial;
        }

    protected:
        sf::Vector2f posInicial;

};