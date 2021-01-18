#pragma once

#include <SFML/Graphics.hpp>
#include "Utils.hpp"
#include "SizedVector.hpp"

class Planet {
public:
    // Velocity vector
    sf::Vector2<fpt> v;

    // Position vector
    sf::Vector2<fpt> p;

    sf::Texture texture;

    // Mass in kg. Will also be used als weight in Newton for simplification
    fpt m{};

    fpt r;

    sf::Color color;

    SizedVector<sf::Vector2<fpt>> history{300};

    bool isStar = false;

    Planet(sf::Vector2<fpt> p, fpt m, sf::Color color, fpt r, const sf::Texture& texture);

    Planet(sf::Vector2<fpt> p, fpt m, sf::Vector2<fpt> v, sf::Color color, fpt r, const sf::Texture& texture);

    void draw(sf::RenderWindow &window);

    [[nodiscard]] sf::Vector2<fpt> gForce(const std::vector<Planet> &planets) const;

    friend std::ostream &operator<<(std::ostream &os, const Planet &planet);

    bool operator==(const Planet &rhs) const;

    bool operator!=(const Planet &rhs) const;
};