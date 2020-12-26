#include <iostream>
#include <SFML/Graphics.hpp>
#include "utils.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Newton's gravitation", sf::Style::Default);

    sf::Event event;

    std::vector<Planet> planets;
    planets.reserve(10);
    std::default_random_engine engine(NOW);
    std::uniform_real_distribution<float> x_dist(0, WINDOW_WIDTH);
    std::uniform_real_distribution<float> y_dist(0, WINDOW_HEIGHT);
    std::uniform_real_distribution<float> m_dist(0, 10);
    for (int i = 0; i < 10; i++) {
        planets.push_back(Planet(sf::Vector2f{x_dist(engine), y_dist(engine)}, m_dist(engine)));
    }

    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::EventType::Closed) {
                std::exit(0);
            }
        }

        window.clear(sf::Color::Black);
        for (auto &planet : planets) {
            planet.draw(window);
        }
        window.display();
    }

    return 0;
}
