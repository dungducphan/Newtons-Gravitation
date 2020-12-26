#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <ostream>
#include <random>
#include <chrono>

#define PI 3.14159265
#define DEG2RAD(x) ((x)*PI/180)
#define RAD2DEG(x) ((x)*180/PI)
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 1200
#define CENTER sf::Vector2f{WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2}
#define UGC 0.00000000006674f
#define MAX(x, y) (((x) > (y)) ? (x) : (y))
#define MIN(x, y) (((x) < (y)) ? (x) : (y))


#define LOG_DEBUG(x) do { std::cout << "[DEBUG] " << __FILE__ << ":" << __LINE__ << ":" << __func__ << "() " << x << std::endl; } while (0);

#define LOG_ERROR(x) do { std::cerr << "[ERROR] " << __FILE__ << ":" << __LINE__ << ":" << __func__ << "() " << x << std::endl; } while (0);

#define LOG_WARNING(x) do { std::cerr << "[WARNING] " << __FILE__ << ":" << __LINE__ << ":" << __func__ << "() " << x << std::endl; } while (0);

#define LOG_INFO(x) do { std::cout << "[INFO] " << __FILE__ << ":" << __LINE__ << ":" << __func__ << "() " << x << std::endl; } while (0);

#define NOW std::chrono::duration_cast<std::chrono::milliseconds>( std::chrono::system_clock::now().time_since_epoch()).count()

typedef double fpt;

class Planet: public sf::CircleShape{
public:
    // Velocity vector
    sf::Vector2<fpt> v;

    // Position vector
    sf::Vector2<fpt> p;

    // Mass in kg. Will also be used als weight in Newton for simplification
    fpt m{};

    bool isStar = false;

    Planet(sf::Vector2<fpt> p, float m);

    void draw(sf::RenderWindow& window) const;

    [[nodiscard]] sf::Vector2<fpt> gForce(const std::vector<Planet>& planets) const ;

    friend std::ostream &operator<<(std::ostream &os, const Planet &planet);

    bool operator==(const Planet &rhs) const;

    bool operator!=(const Planet &rhs) const;
};

fpt sfAbs(const sf::Vector2<fpt>& vec);

std::ostream &operator<<(std::ostream &os, const sf::Vector2<fpt> &vector);

sf::Vector2<fpt> operator+(const sf::Vector2<fpt>& lhs, fpt scalar);

sf::Vector2<fpt> operator-(const sf::Vector2<fpt>& lhs, fpt scalar);

sf::Vector2<fpt> operator/(const sf::Vector2<fpt>& lhs, fpt scalar);

sf::Vector2<fpt> operator*(const sf::Vector2<fpt>& lhs, fpt scalar);