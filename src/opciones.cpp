#include "../include/opciones.hpp"
#include "../include/juego.hpp"
#include "../include/partida.hpp"
#include "../include/menu.hpp"

Opciones::Opciones(bool vieneDelMenu) : 
    desdeMenu(vieneDelMenu),
    opcionSeleccionada(0),
    nivelVolumen(5),
    fuente("./assets/fuente.ttf"),
    textoVolumen(fuente),
    textoVolver(fuente),
    textoSalir(fuente),
    spriteFondoOpciones(texturaFondoOpciones)
{
    if (texturaFondoOpciones.loadFromFile("./assets/menu_fondo.png")) {
        spriteFondoOpciones.setTexture(texturaFondoOpciones, true);
        sf::Vector2u tam = texturaFondoOpciones.getSize();
        spriteFondoOpciones.setScale({384.f / tam.x, 384.f / tam.y});
    }

    //perilla de volumen
    sliderVolumen.setSize({5.f, 20.f}); 
    sliderVolumen.setFillColor(sf::Color::White);
    sliderVolumen.setOutlineColor(sf::Color::Black);
    sliderVolumen.setOutlineThickness(2.f);
    sliderVolumen.setOrigin({5.f, 12.5f}); 
    sliderVolumen.setPosition({125.f + (nivelVolumen * 14.f), 207.f});

    barraVolumen.setSize({140.f, 14.f});
    barraVolumen.setFillColor(sf::Color(150, 150, 150));
    barraVolumen.setPosition({125.f, 185.f});

    //cambia dependiendo de si venimos del menú o de la partida
    if(desdeMenu) {
        textoVolver.setString("VOLVER AL MENU");
        textoSalir.setString(""); 
    } else {
        textoVolver.setString("VOLVER A PARTIDA");
        textoSalir.setString("MENU PRINCIPAL");
    }
    
    textoVolver.setCharacterSize(19);
    textoVolver.setFillColor(sf::Color::White);
    textoVolver.setOutlineColor(sf::Color::Black);
    textoVolver.setOutlineThickness(3.f);
    textoVolver.setPosition({120.f, 220.f}); 

    textoSalir.setCharacterSize(19);
    textoSalir.setFillColor(sf::Color::White);
    textoSalir.setOutlineColor(sf::Color::Black);
    textoSalir.setOutlineThickness(3.f);
    textoSalir.setPosition({120.f, 250.f});


    textoVolumen.setString("Volumen: " + std::to_string(nivelVolumen));
    textoVolumen.setCharacterSize(22);
    textoVolumen.setFillColor(sf::Color::Black);
    textoVolumen.setOutlineColor(sf::Color::White);
    textoVolumen.setOutlineThickness(1.5f);
    textoVolumen.setPosition({138.f, 150.f});
}

void Opciones::renderizar(sf::RenderWindow &ventana){
    ventana.draw(spriteFondoOpciones); 
    ventana.draw(barraVolumen);
    ventana.draw(sliderVolumen);
    ventana.draw(textoVolumen);
    ventana.draw(textoVolver);
    if(!desdeMenu) ventana.draw(textoSalir); 
}

void Opciones::actualizar(Juego &juego){
    textoVolver.setFillColor(sf::Color::White);
    textoVolver.setOutlineColor(sf::Color::Black);
    textoSalir.setFillColor(sf::Color::White);
    textoSalir.setOutlineColor(sf::Color::Black);

    if(opcionSeleccionada == 1) { 
        textoVolver.setFillColor(sf::Color::Yellow);
    }
    else if(opcionSeleccionada == 2) {
        textoSalir.setFillColor(sf::Color::Yellow);
    }

    textoVolumen.setString("Volumen: " + std::to_string(nivelVolumen));
    sliderVolumen.setPosition({125.f + (nivelVolumen * 14.f), 195.f});
}

void Opciones::procesarEvento(Juego &juego, const sf::Event &evento){
    if(const auto* teclaPresionada = evento.getIf<sf::Event::KeyPressed>()){
        
        //pregunta de donde viene, menu 1 , partida 2
        int maxOpciones = desdeMenu ? 1 : 2; 

        if(teclaPresionada->code == sf::Keyboard::Key::Up || teclaPresionada->code == sf::Keyboard::Key::W){
            if(opcionSeleccionada > 0) opcionSeleccionada--;
        }
        else if(teclaPresionada->code == sf::Keyboard::Key::Down || teclaPresionada->code == sf::Keyboard::Key::S){
            if(opcionSeleccionada < maxOpciones) opcionSeleccionada++;
        }
        else if (teclaPresionada->code == sf::Keyboard::Key::Enter) {
        if (opcionSeleccionada == 1) { 
            if (desdeMenu) {
            juego.cambiarEscena(new Menu()); 
        } else {
            juego.reanudarJuego(); 
        };
    }
    else if (opcionSeleccionada == 2 && !desdeMenu) {
        juego.cambiarEscena(new Menu());
    }
}
        
        if(opcionSeleccionada == 0){
            if(teclaPresionada->code == sf::Keyboard::Key::Left || teclaPresionada->code == sf::Keyboard::Key::A){
                if(nivelVolumen > 0) nivelVolumen--;
            }
            else if(teclaPresionada->code == sf::Keyboard::Key::Right || teclaPresionada->code == sf::Keyboard::Key::D){
                if(nivelVolumen < 10) nivelVolumen++;
            }
        }
    }
}