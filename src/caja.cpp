#include "../include/caja.hpp"

Caja::Caja(sf::Vector2f posInicial, bool estaEnObjetivo) {
    this->posInicial = posInicial;
    this->enObjetivo = estaEnObjetivo;
}

void Caja::renderizar(sf::RenderWindow& ventana, sf::Texture& texturaNormal, sf::Texture& texturaObjetivo) {
    sf::Texture& texturaAUsar = enObjetivo ? texturaObjetivo : texturaNormal;
    sf::Sprite spriteCaja(texturaAUsar);
    
    spriteCaja.setPosition(posInicial);
    ventana.draw(spriteCaja);
}

void Caja::setEnObjetivo(bool estado) {
    enObjetivo = estado;
}

bool Caja::isEnObjetivo() const {
    return enObjetivo;
}