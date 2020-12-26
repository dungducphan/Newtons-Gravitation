#include "utils.hpp"


Planet::Planet(sf::Vector2<fpt> p, float m, sf::Color color, fpt r) : p(p), m(m), color(color), r(r) {}

Planet::Planet(sf::Vector2<fpt> p, float m, sf::Vector2<fpt> v, sf::Color color, fpt r) : p(p), m(m), v(v),
                                                                                          color(color), r(r) {

}

std::ostream &operator<<(std::ostream &os, const Planet &planet) {
    os << "[Velocity vector: " << planet.v << ", Mass: " << planet.m << ", Position vector: " << planet.p << "]";
    return os;
}

void Planet::draw(sf::RenderWindow &window) const {
    if (!this->isStar) {
        sf::CircleShape circle;
        circle.setRadius(r);
        sf::Vector2<fpt> pos(this->p - sf::Vector2<fpt>{r, r});
        circle.setPosition(pos.x, pos.y);
        circle.setFillColor(this->color);
        window.draw(circle);
    } else {
        int width = 660;
        int height = 660;
        sf::Texture texture;
        if (!texture.loadFromFile("sun.png", sf::IntRect(0, 0, width, height))){
            LOG_ERROR("Can not load sun.png. Exit now")
            std::exit(1);
        }
        sf::Sprite sprite{texture};
        sf::Vector2f targetSize(this->r, this->r);
        sprite.setScale(
                targetSize.x / sprite.getLocalBounds().width,
                targetSize.y / sprite.getLocalBounds().height);
        sf::Vector2<fpt> pos(this->p - sf::Vector2<fpt>{r, r});
        sprite.setPosition(pos.x, pos.y);
        window.draw(sprite);
    }
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
           m == rhs.m &&
           color == rhs.color &&
           r == rhs.r &&
           isStar == rhs.isStar;
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