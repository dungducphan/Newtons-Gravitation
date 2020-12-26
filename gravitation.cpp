#include <iostream>
#include <SFML/Graphics.hpp>
#include "utils.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Newton's gravitation", sf::Style::Default);
    sf::Event event;

    std::vector<Planet> planets;
    planets.emplace_back(sf::Vector2<fpt>(200.0f, 400.0f), 2);
    planets.back().v = sf::Vector2<fpt>(0.f, -0.01);
    planets.emplace_back(sf::Vector2<fpt>(400.0f, 400.0f), 1000000000);
    planets.back().isStar = true;


    float deltaT = 0.f;

    sf::Clock clock;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::EventType::Closed) {
                std::exit(0);
            }
        }

        std::vector<sf::Vector2<fpt>> deltaVs;

        // Simulate one second
        for (auto &planet : planets) {
            if(!planet.isStar) {
                sf::Vector2<fpt> gForce = planet.gForce(planets);
                sf::Vector2<fpt> a = gForce * planet.m;
                sf::Vector2<fpt> deltaV = a * deltaT;
                deltaVs.push_back(deltaV);
            } else {
                deltaVs.emplace_back(0, 0);
            }
        }

        for (int i = 0; i < deltaVs.size(); i++) {
            if (!planets[i].isStar) {
                planets[i].v += deltaVs[i];
                sf::Vector2<fpt> deltaS = planets[i].v * deltaT;
                planets[i].p += deltaS;
                LOG_INFO(planets[i]);
            }
        }

        window.clear(sf::Color::Black);
        for (auto &planet : planets) {
            planet.draw(window);
        }
        window.display();
        deltaT = clock.restart().asSeconds() * 1000;
    }

    return 0;
    }
