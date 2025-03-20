#include <SFML/Graphics.hpp>

int main() {

    sf::RenderWindow window(sf::VideoMode(1000,1000), L"Домашнее задание №1");
    sf::CircleShape shape (200.f);
    shape.setPosition({300, 300});
    shape.setFillColor(sf::Color::Green);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){ window.close(); }
                
        }
        window.clear();
        window.draw(shape);
        window.display();
    }


    return 0;
}
