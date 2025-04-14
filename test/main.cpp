#include <SFML/Graphics.hpp>
#include <iostream>

int main() {

    sf::RenderWindow window(sf::VideoMode(500,500),"test");
    sf::RectangleShape rectangle(sf::Vector2f(120,50));
    rectangle.setFillColor(sf::Color::Red);

    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
    window.clear();
    window.draw(rectangle);
    window.display();
    
    }

   

    return 0;
}