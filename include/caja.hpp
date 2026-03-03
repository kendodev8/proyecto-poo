#pragma once
#include <SFML/Graphics.hpp>
#include "../include/entidad.hpp"

class Caja : public Entidad {
public:
    Caja(sf::Vector2f posInicial, bool estaEnObjetivo);
    void renderizar(sf::RenderWindow& ventana, sf::Texture& texturaNormal, sf::Texture& texturaObjetivo);
    void setEnObjetivo(bool estado);
    bool isEnObjetivo() const;

private:
    bool enObjetivo;
};