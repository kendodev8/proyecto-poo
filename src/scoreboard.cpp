#include "../include/scoreboard.hpp"
#include "../include/juego.hpp"
#include "../include/menu.hpp"
#include "../include/scoremanager.hpp"
#include <string>
#include <algorithm>

Scoreboard::Scoreboard() :
    fuente("./assets/fuente.ttf"),
    textoNivel(fuente)
{
    textoNivel.setString("NIVEL 1");
    textoNivel.setPosition({150.f, 50.f});
    textoNivel.setCharacterSize(30);
    textoNivel.setFillColor(sf::Color::White);
    textoNivel.setOutlineColor(sf::Color::Black);
    textoNivel.setOutlineThickness(4.f);

    opcionSeleccionada = 0;
}

void Scoreboard::renderizar(sf::RenderWindow &ventana){
    ventana.draw(textoNivel);

    for(auto texto : textoScores){
        ventana.draw(texto);
    }
}

void Scoreboard::actualizar(Juego &juego){
    textoNivel.setFillColor(sf::Color::White);

    switch(opcionSeleccionada)
    {
        case 0:
            textoNivel.setFillColor(sf::Color::Yellow);
            textoNivel.setString("Nivel " + std::to_string(opcionSeleccionada + 1));
            break;
        case 1:
            textoNivel.setFillColor(sf::Color::Yellow);
            textoNivel.setString("Nivel " + std::to_string(opcionSeleccionada + 1));
            break;
        case 2:
            textoNivel.setFillColor(sf::Color::Yellow);
            textoNivel.setString("Nivel " + std::to_string(opcionSeleccionada + 1));
            break;
        case 3:
            textoNivel.setFillColor(sf::Color::Yellow);
            textoNivel.setString("Nivel " + std::to_string(opcionSeleccionada + 1));
            break;
        case 4:
            textoNivel.setFillColor(sf::Color::Yellow);
            textoNivel.setString("Nivel " + std::to_string(opcionSeleccionada + 1));
            break;
        case 5:
            textoNivel.setFillColor(sf::Color::Yellow);
            textoNivel.setString("Nivel " + std::to_string(opcionSeleccionada + 1));
            break;
        case 6:
            textoNivel.setFillColor(sf::Color::Yellow);
            textoNivel.setString("Nivel " + std::to_string(opcionSeleccionada + 1));
            break;
    }

    auto totalScores = juego.getRegistroScores();

    std::vector<score> filtrados;

    for(const auto& score : totalScores){
        if(score.nivel == opcionSeleccionada) filtrados.push_back(score);
    }

    std::sort(filtrados.begin(), filtrados.end(),
        [](const score &a, const score &b)
        {
            return a.movimientos < b.movimientos;
        });

    if(filtrados.size() > 10) filtrados.resize(10);

    for(size_t i = 0; i < filtrados.size(); ++i){
        sf::Text textoScoreIndividual(fuente);
        std::string nombre(filtrados[i].nombre);

        if(opcionSeleccionada == filtrados[i].nivel){
            textoScoreIndividual.setString(
                nombre +
                " - Movimientos: " + std::to_string(filtrados[i].movimientos));

            textoScoreIndividual.setCharacterSize(16);
            textoScoreIndividual.setPosition({75.f, 85.f + static_cast<float>(i) * 25.f});

            textoScores.push_back(textoScoreIndividual);
        }
    }
}

void Scoreboard::procesarEvento(Juego &juego, const sf::Event &evento){
    if(const auto* teclaPresionada = evento.getIf<sf::Event::KeyPressed>()){
        if(teclaPresionada->code == sf::Keyboard::Key::Left|| teclaPresionada->code == sf::Keyboard::Key::A){
            if(opcionSeleccionada > 0){
                opcionSeleccionada--;
                textoScores.clear();
            } 
        }
        else if(teclaPresionada->code == sf::Keyboard::Key::Right || teclaPresionada->code == sf::Keyboard::Key::D){
            if(opcionSeleccionada < 6){
                opcionSeleccionada++;
                textoScores.clear();
            }
        }
        else if(teclaPresionada->code == sf::Keyboard::Key::Escape){
            juego.cambiarEscena(new Menu);
        }
    }
}