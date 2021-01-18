#pragma once

#include <SFML/Graphics.hpp>
#include <sstream>
#include <vector>
#include "Utils.hpp"
#include "Planet.hpp"

class Universe {
    sf::Texture sunTexture;
    std::vector<sf::Texture> planetTextures;

    std::default_random_engine engine;
    std::vector<Planet> planets;
    std::uniform_real_distribution<fpt> red_dist{200, 255};
    std::uniform_real_distribution<fpt> green_dist{200, 255};
    std::uniform_real_distribution<fpt> blue_dist{200, 255};
    std::uniform_real_distribution<fpt> alpha_dist{100, 150};
    sf::Event event{};
    sf::RenderWindow *window;
    sf::Font *font;
    float deltaT = 0.f;
    float speed = 10000.0f;
    FPS fps;

    sf::Clock clock;

    void simulate();

    void infoText();

public:
    explicit Universe(sf::RenderWindow *window, sf::Font *font);

    void run();
};