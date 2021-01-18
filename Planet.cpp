#include "Planet.hpp"


Planet::Planet(sf::Vector2<fpt> p, fpt m, sf::Color color, fpt r, const sf::Texture &texture) : p(p), m(m),
                                                                                                color(color), r(r),
                                                                                                texture(texture) {}

Planet::Planet(sf::Vector2<fpt> p, fpt m, sf::Vector2<fpt> v, sf::Color color, fpt r, const sf::Texture &texture) : p(
        p), m(m), v(v),
                                                                                                                    color(color),
                                                                                                                    r(r),
                                                                                                                    texture(texture) {
}

void Planet::draw(sf::RenderWindow &window) {
    // Rotate planets
    if(!this->isStar) {
        this->history.push_back(p);
    }

    // Planet motion

    sf::Sprite sprite{texture};
    sf::Vector2f targetSize(this->r, this->r);
    sprite.setScale(
            targetSize.x / sprite.getLocalBounds().width,
            targetSize.y / sprite.getLocalBounds().height);
    sf::Vector2<fpt> spriteP(this->p - sf::Vector2<fpt>{r / 2, r / 2});
    sprite.setPosition(spriteP.x, spriteP.y);
    window.draw(sprite);

    // Draw history
    for(int32_t i = 0; i < this->history.size(); i++) {
        sf::CircleShape circle(1);
        circle.setPosition(history[i].x, history[i].y);
        circle.setFillColor(sf::Color::White);
        window.draw(circle);
    }

    // Debug
    sf::CircleShape circle(1);
    circle.setPosition(p.x, p.y);
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
           m == rhs.m &&
           color == rhs.color &&
           r == rhs.r &&
           isStar == rhs.isStar;
}

bool Planet::operator!=(const Planet &rhs) const {
    return !(rhs == *this);
}

std::ostream &operator<<(std::ostream &os, const Planet &planet) {
    os << "[Velocity vector: " << planet.v << ", Mass: " << planet.m << ", Position vector: " << planet.p << "]";
    return os;
}

