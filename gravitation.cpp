#include <iostream>
#include <SFML/Graphics.hpp>
#include "utils.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Newton's gravitation", sf::Style::Default);

    sf::Event event;
    while(window.isOpen()){
        while(window.pollEvent(event)){
            if(event.type == sf::Event::EventType::Closed){
                std::exit(0);
            }
        }

        LOG_INFO("Hello world");
    }

    return 0;
}
