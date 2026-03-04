#include "../include/victoria.hpp"
#include "../include/juego.hpp"
#include "../include/menu.hpp"

Victoria::Victoria() : 
    fuente("./assets/fuente.ttf"),
    textoVictoria(fuente),
    textoSalir(fuente)
{
    if (texturaFondoVictoria.loadFromFile("./assets/fondoVictoria.png")) {
        fondoVictoria.setSize(sf::Vector2f(384.f, 384.f));
        fondoVictoria.setTexture(&texturaFondoVictoria);
    }

    textoVictoria.setString("FELICITACIONES!\nPasaste todo el juego");
    textoVictoria.setCharacterSize(24);
    textoVictoria.setFillColor(sf::Color::White);
    textoVictoria.setOutlineColor(sf::Color::Black);
    textoVictoria.setOutlineThickness(4.f);
    textoVictoria.setPosition({85.f, 150.f});

    textoSalir.setString("MENU PRINCIPAL");
    textoSalir.setCharacterSize(22);
    textoSalir.setFillColor(sf::Color::Yellow);
    textoSalir.setOutlineColor(sf::Color::Black);
    textoSalir.setOutlineThickness(4.f);
    textoSalir.setPosition({105.f, 250.f});

    if (musicaVictoria.openFromFile("./assets/victoria.mp3")) {
    musicaVictoria.setVolume(50.f);
    musicaVictoria.play();
}
}
void Victoria::actualizar(Juego &juego) {}

void Victoria::renderizar(sf::RenderWindow &ventana) {
    ventana.draw(fondoVictoria);
    ventana.draw(textoVictoria);
    ventana.draw(textoSalir);
}

void Victoria::procesarEvento(Juego &juego, const sf::Event &evento) {
    if(const auto* teclaPresionada = evento.getIf<sf::Event::KeyPressed>()){
        if(teclaPresionada->code == sf::Keyboard::Key::Enter){
            juego.cambiarEscena(new Menu()); // Volvemos al inicio
        } else if(teclaPresionada->code == sf::Keyboard::Key::Escape){
            // Salir del juego (opcional)
        }
    }
}