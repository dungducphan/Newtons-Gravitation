#include <iostream>
#include <SFML/Graphics.hpp>
#include "utils.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Newton's gravitation", sf::Style::Default);
    sf::Event event;
    std::default_random_engine engine(NOW);
    std::uniform_real_distribution<fpt> red_dist(200, 255);
    std::uniform_real_distribution<fpt> green_dist(200, 255);
    std::uniform_real_distribution<fpt> blue_dist(200, 255);
    std::uniform_real_distribution<fpt> alpha_dist(100, 150);
    std::vector<Planet> planets;

    planets.emplace_back(sf::Vector2<fpt>(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), 1000000000, sf::Vector2<fpt>(0.f, -0.005),
                         sf::Color(200, 32, 125, 200), 50);
    planets.back().isStar = true;


    float deltaT = 0.f;
    float speed = 10000.0f;

    sf::Clock clock;
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::EventType::Closed) {
                std::exit(0);
            }
            if (event.type == sf::Event::EventType::MouseButtonPressed) {
                fpt x = event.mouseButton.x;
                fpt y = event.mouseButton.y;
                Planet planet(sf::Vector2<fpt>(x, y), 1000, sf::Vector2<fpt>(0.01f, -0.01),
                              sf::Color(red_dist(engine), green_dist(engine), blue_dist(engine), alpha_dist(engine)),
                              10);

                if (x < WINDOW_WIDTH / 2 && y < WINDOW_HEIGHT / 2) {
                    planet.v = sf::Vector2<fpt>(0.01f, -0.01);
                } else if (x > WINDOW_WIDTH / 2 && y < WINDOW_HEIGHT / 2) {
                    planet.v = sf::Vector2<fpt>(0.01f, 0.01);
                } else if (x < WINDOW_WIDTH / 2 && y > WINDOW_HEIGHT / 2) {
                    planet.v = sf::Vector2<fpt>(-0.01f, -0.01);
                } else {
                    planet.v = sf::Vector2<fpt>(-0.01f, 0.01);
                }

                planets.push_back(planet);
            }
        }

        std::vector<sf::Vector2<fpt>> deltaVs;

        // Simulate one second
        for (auto &planet : planets) {
            if (!planet.isStar) {
                sf::Vector2<fpt> f = planet.gForce(planets);
                sf::Vector2<fpt> a = f / planet.m;
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
            }
        }

        window.clear(sf::Color::Black);
        for (auto &planet : planets) {
            planet.draw(window);
        }
        window.display();
        deltaT = clock.restart().asSeconds() * speed;
    }

    return 0;
}
