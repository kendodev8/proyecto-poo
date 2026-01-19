#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Hotline Palermo");

    sf::RectangleShape shape({16.f, 16.f});
    shape.setPosition({400.f, 200.f});

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()){
            if (event->is<sf::Event::Closed>()){
                window.close();
            }
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}