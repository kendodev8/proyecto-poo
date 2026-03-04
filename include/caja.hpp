#pragma once
#include "entidad.hpp"

class Caja : public Entidad {
public:
    Caja(sf::Vector2f posInicial, bool estaEnObjetivo);
    void renderizar(sf::RenderWindow &ventana, sf::Texture &texturaNormal, sf::Texture &texturaObjetivo);
    void setEnObjetivo(bool estado);
    bool getEnObjetivo() const;

private:
    bool enObjetivo;
};