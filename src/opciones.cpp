#include "../include/opciones.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "../include/juego.hpp"
#include "../include/partida.hpp"
#include "../include/menu.hpp"

Opciones::Opciones() :
    fuente("./assets/fuente.ttf"),
    textoVolver(fuente),
    textoSalir(fuente),
    textoVolumen(fuente),
    sliderVolumen(texturaUI)
{
    if(texturaUI.loadFromFile("./assets/ui_cuadrado.png")){
        sliderVolumen.setTexture(texturaUI, true);
        sliderVolumen.setPosition({170.f, 185.f});
        sliderVolumen.setScale({0.10f, 0.8f});
    }

    textoVolver.setString("VOLVER");
    textoVolver.setCharacterSize(22);
    textoVolver.setFillColor(sf::Color::White);
    textoVolver.setOutlineColor(sf::Color::Black);
    textoVolver.setOutlineThickness(4.f);
    textoVolver.setPosition({147.f, 230.f});

    textoSalir.setString("MENU PRINCIPAL");
    textoSalir.setCharacterSize(22);
    textoSalir.setFillColor(sf::Color::White);
    textoSalir.setOutlineColor(sf::Color::Black);
    textoSalir.setOutlineThickness(4.f);
    textoSalir.setPosition({105.f, 265.f});

    textoVolumen.setString("Volumen: 5");
    textoVolumen.setCharacterSize(22);
    textoVolumen.setFillColor(sf::Color::Black);
    textoVolumen.setOutlineColor(sf::Color::White);
    textoVolumen.setOutlineThickness(2.f);
    textoVolumen.setPosition({138.f, 150.f});

    opcionSeleccionada = 0;
    nivelVolumen = 5;
}

void Opciones::renderizar(sf::RenderWindow &ventana){
    ventana.draw(textoVolumen);
    ventana.draw(barraVolumen);
    ventana.draw(sliderVolumen);
    ventana.draw(textoVolver);
    ventana.draw(textoSalir);
}

void Opciones::actualizar(Juego &juego){
    textoVolumen.setFillColor(sf::Color::Black);
    textoVolver.setFillColor(sf::Color::White);
    textoSalir.setFillColor(sf::Color::White);

    if(opcionSeleccionada == 0) textoVolumen.setFillColor(sf::Color(80, 80, 80));
    if(opcionSeleccionada == 1) textoVolver.setFillColor(sf::Color::Yellow);
    if(opcionSeleccionada == 2) textoSalir.setFillColor(sf::Color::Yellow);

    float porcentaje = nivelVolumen * 10.f;
    textoVolumen.setString("Volumen: " + std::to_string(nivelVolumen));
    sliderVolumen.setPosition({125.f + (nivelVolumen * 14.f), 195.f});
}

void Opciones::procesarEvento(Juego &juego, const sf::Event &evento){
    if(const auto* teclaPresionada = evento.getIf<sf::Event::KeyPressed>()){
        if(teclaPresionada->code == sf::Keyboard::Key::Up || teclaPresionada->code == sf::Keyboard::Key::W){
            if(opcionSeleccionada > 0){
                opcionSeleccionada--;
            }
        }
        else if(teclaPresionada->code == sf::Keyboard::Key::Down || teclaPresionada->code == sf::Keyboard::Key::S){
            if(opcionSeleccionada < 2){
                opcionSeleccionada++;
            }
        }
        else if(teclaPresionada->code == sf::Keyboard::Key::Enter){
            if(opcionSeleccionada == 1){
                juego.cambiarEscena(new Partida);
            }
            else if(opcionSeleccionada == 2){
                juego.cambiarEscena(new Menu);
            }
        }

        if(opcionSeleccionada == 0){
            if(teclaPresionada->code == sf::Keyboard::Key::Left || teclaPresionada->code == sf::Keyboard::Key::A){
                if(nivelVolumen > 0){
                    nivelVolumen--;
                }
            }
            else if(teclaPresionada->code == sf::Keyboard::Key::Right || teclaPresionada->code == sf::Keyboard::Key::D){
                if(nivelVolumen < 10){
                    nivelVolumen++;
                }
            }
        }
    }
}