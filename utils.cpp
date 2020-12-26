#include "utils.hpp"


Planet::Planet(sf::Vector2f p, float m) : p(p), m(m), f(sf::Vector2f{0, 0}) {
    std::default_random_engine engine(NOW);
    std::uniform_real_distribution<float> dist(0, 255);
    this->color = sf::Color(dist(engine), dist(engine), dist(engine), 200);
}

std::ostream &operator<<(std::ostream &os, const Planet &planet) {
    os << "[Force vector: " << planet.f << ", Mass: " << planet.m << ", Velocity: " << planet.v << ", Position vector: " << planet.p << "]";
    return os;
}

bool Planet::operator==(const Planet &rhs) const {
    return f == rhs.f && m == rhs.m && v == rhs.v && p == rhs.p;
}

bool Planet::operator!=(const Planet &rhs) const {
    return !(rhs == *this);
}

void Planet::draw(sf::RenderWindow& window) const {
    sf::CircleShape circle(this->m);
    circle.setPosition(this->p - sf::Vector2f{this->m / 2, this->m/2});
    circle.setFillColor(this->color);
    window.draw(circle);
}

std::ostream &operator<<(std::ostream &os, const sf::Vector2f &vector) {
    os << "[x = " << vector.x << ", y = " << vector.y << "]";
    return os;
}
