#include "../include/menu.hpp"
#include <SFML/Window.hpp>
#include "../include/juego.hpp"
#include "../include/partida.hpp"
#include "../include/opciones.hpp"

Menu::Menu() :
    fuente("./assets/fuente.ttf"),
    textoJugar(fuente),
    textoScoreboard(fuente),
    spriteFondoMenu(texturaFondoMenu)
{
    if (texturaFondoMenu.loadFromFile("./assets/menu_fondo.png")) {
        spriteFondoMenu.setTexture(texturaFondoMenu, true);
        sf::Vector2u tam = texturaFondoMenu.getSize();
        spriteFondoMenu.setScale({384.f / tam.x, 384.f / tam.y});
    }
    
    textoJugar.setString("JUGAR");
    textoJugar.setPosition({150.f, 150.f});
    textoJugar.setCharacterSize(30);
    textoJugar.setFillColor(sf::Color::White);
    textoJugar.setOutlineColor(sf::Color::Black);
    textoJugar.setOutlineThickness(4.f);

    textoScoreboard.setString("OPCIONES");
    textoScoreboard.setPosition({130.f, 200.f});
    textoScoreboard.setCharacterSize(30);
    textoScoreboard.setFillColor(sf::Color::White);
    textoScoreboard.setOutlineColor(sf::Color::Black);
    textoScoreboard.setOutlineThickness(4.f);

    opcionSeleccionada = 0;
}

void Menu::renderizar(sf::RenderWindow &ventana){
    ventana.draw(spriteFondoMenu);
    ventana.draw(textoJugar);
    ventana.draw(textoScoreboard);
}

void Menu::actualizar(Juego &juego){
    textoJugar.setFillColor(sf::Color::White);
    textoScoreboard.setFillColor(sf::Color::White);

    if(opcionSeleccionada == 0) textoJugar.setFillColor(sf::Color::Yellow);
    if(opcionSeleccionada == 1) textoScoreboard.setFillColor(sf::Color::Yellow);
}

void Menu::procesarEvento(Juego &juego, const sf::Event &evento){
    if(const auto* teclaPresionada = evento.getIf<sf::Event::KeyPressed>()){
            if(teclaPresionada->code == sf::Keyboard::Key::Up || teclaPresionada->code == sf::Keyboard::Key::W){
                opcionSeleccionada = 0;
                //if(sonidoSelect) sonidoSelect->play();
            }
            else if(teclaPresionada->code == sf::Keyboard::Key::Down || teclaPresionada->code == sf::Keyboard::Key::S){
                opcionSeleccionada = 1;
                //if(sonidoSelect) sonidoSelect->play();
            }
            else if(teclaPresionada->code == sf::Keyboard::Key::Enter){
                if(opcionSeleccionada == 0) {
                    juego.cambiarEscena(new Partida);
                }
                else if(opcionSeleccionada == 1) {
                    juego.cambiarEscena(new Opciones(true));
                    opcionSeleccionada = 0;
                }
            }
        }
}