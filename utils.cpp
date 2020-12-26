#include "utils.hpp"


Planet::Planet(sf::Vector2<fpt> p, float m) : p(p), m(m) {}

std::ostream &operator<<(std::ostream &os, const Planet &planet) {
    os << "[Velocity vector: " << planet.v << ", Mass: " << planet.m << ", Position vector: " << planet.p << "]";
    return os;
}

void Planet::draw(sf::RenderWindow &window) const {
    sf::CircleShape circle;
    circle.setRadius(MIN(this->m, 50));
    sf::Vector2<fpt> pos(this->p - sf::Vector2<fpt>{MIN(this->m, 50) / 2, MIN(this->m, 50) / 2});
    circle.setPosition(pos.x, pos.y);
    circle.setFillColor(sf::Color::Red);
    window.draw(circle);
}

sf::Vector2<fpt> Planet::gForce(const std::vector<Planet> &planets) const {
    sf::Vector2<fpt> ret(0, 0);
    for (const auto &planet : planets) {
        if (planet != *this) {
            sf::Vector2<fpt> direction = planet.p - this->p;
            fpt distance = sfAbs(direction);
            ret += planet.m * (direction / std::pow(distance, 3));
        }
    }
    ret *= this->m * UGC;
    return ret;
}

bool Planet::operator==(const Planet &rhs) const {
    return v == rhs.v &&
           p == rhs.p &&
           isStar == rhs.isStar &&
           m == rhs.m ;
}

bool Planet::operator!=(const Planet &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const sf::Vector2<fpt> &vector) {
    os << "[x = " << vector.x << ", y = " << vector.y << "]";
    return os;
}

fpt sfAbs(const sf::Vector2<fpt> &vec) {
    return std::sqrt(std::pow(vec.x, 2.0f) + std::pow(vec.y, 2.0f));
}

sf::Vector2<fpt> operator+(const sf::Vector2<fpt> &lhs, fpt scalar) {
    sf::Vector2<fpt> ret(lhs);
    ret.x += scalar;
    ret.y += scalar;
    return ret;
}

sf::Vector2<fpt> operator-(const sf::Vector2<fpt> &lhs, fpt scalar) {
    sf::Vector2<fpt> ret(lhs);
    ret.x -= scalar;
    ret.y -= scalar;
    return ret;
}

sf::Vector2<fpt> operator/(const sf::Vector2<fpt> &lhs, fpt scalar) {
    sf::Vector2<fpt> ret(lhs);
    ret.x /= scalar;
    ret.y /= scalar;
    return ret;
}

sf::Vector2<fpt> operator*(const sf::Vector2<fpt> &lhs, fpt scalar) {
    sf::Vector2<fpt> ret(lhs);
    ret.x *= scalar;
    ret.y *= scalar;
    return ret;
}