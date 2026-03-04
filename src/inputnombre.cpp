#include "../include/inputnombre.hpp"
#include "../include/juego.hpp"
#include "../include/partida.hpp"

InputNombre::InputNombre() :
    fuente("./assets/fuente.ttf"),
    textoNombre(fuente),
    textoInstruccion(fuente)
{
    textoNombre.setPosition({150.f, 150.f});
    textoNombre.setCharacterSize(30);
    textoNombre.setFillColor(sf::Color::White);
    textoNombre.setOutlineColor(sf::Color::Black);
    textoNombre.setOutlineThickness(4.f);

    textoInstruccion.setString("INGRESAR NOMBRE: ");
    textoInstruccion.setPosition({80.f, 100.f});
    textoInstruccion.setCharacterSize(30);
    textoInstruccion.setFillColor(sf::Color::White);
    textoInstruccion.setOutlineColor(sf::Color::Black);
    textoInstruccion.setOutlineThickness(4.f);
}

void InputNombre::renderizar(sf::RenderWindow &ventana){
    ventana.draw(textoNombre);
    ventana.draw(textoInstruccion);
}

void InputNombre::actualizar(Juego &juego){
    std::string display = nombreJugador;

    while(display.size() < 3) display += "_";

    textoNombre.setString(display);
}

void InputNombre::procesarEvento(Juego &juego, const sf::Event &evento){
    if(const auto* textoIngresado = evento.getIf<sf::Event::TextEntered>()){
        char entered = static_cast<char>(textoIngresado->unicode);

        if (entered == '\b' && !nombreJugador.empty())
        {
            nombreJugador.pop_back();
        }
        else if (std::isalpha(entered) && nombreJugador.size() < 3)
        {
            nombreJugador += std::toupper(entered);
        }
    }

    if (const auto* keyPressed = evento.getIf<sf::Event::KeyPressed>())
    {
        if (keyPressed->code == sf::Keyboard::Key::Enter && nombreJugador.size() == 3)
        {
            juego.setNombreJugador(nombreJugador);
            juego.cambiarEscena(new Partida);
        }
    }
}