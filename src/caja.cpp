#include "../include/caja.hpp"

// Constructor
Caja::Caja(sf::Vector2f posInicial, bool estaEnObjetivo) {
    this->posInicial = posInicial; // Variable heredada de Entidad
    this->enObjetivo = estaEnObjetivo;
}

// La caja se dibuja a sí misma
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