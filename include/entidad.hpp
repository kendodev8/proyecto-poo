#pragma once
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <cstdio>

class Entidad {
    public:
        void setPos(sf::Vector2f pos){
            posInicial = pos;
        }

        sf::Vector2f getPos(){
            return posInicial;
        }

        virtual ~Entidad() = default;

    protected:
        sf::Vector2f posInicial;
};