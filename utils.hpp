#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <ostream>
#include <random>
#include <chrono>

#define PI 3.14159265
#define DEG2RAD(x) ((x)*PI/180)
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 1200
#define CENTER sf::Vector2f{WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2}


#define LOG_DEBUG(x) do { std::cout << "[DEBUG] " << __FILE__ << ":" << __LINE__ << ":" << __func__ << "() " << x << std::endl; } while (0);

#define LOG_ERROR(x) do { std::cerr << "[ERROR] " << __FILE__ << ":" << __LINE__ << ":" << __func__ << "() " << x << std::endl; } while (0);

#define LOG_WARNING(x) do { std::cerr << "[WARNING] " << __FILE__ << ":" << __LINE__ << ":" << __func__ << "() " << x << std::endl; } while (0);

#define LOG_INFO(x) do { std::cout << "[INFO] " << __FILE__ << ":" << __LINE__ << ":" << __func__ << "() " << x << std::endl; } while (0);

#define NOW std::chrono::duration_cast<std::chrono::milliseconds>( std::chrono::system_clock::now().time_since_epoch()).count()

class Planet {
public:
    // Force vector
    sf::Vector2f f;

    // Position vector
    sf::Vector2f p;

    // Mass in kg
    float m{};

    // Velocity
    float v{0.0f};

    sf::Color color;

    Planet(sf::Vector2f p, float m);

    void draw(sf::RenderWindow& window) const;

    friend std::ostream &operator<<(std::ostream &os, const Planet &planet);

    bool operator==(const Planet &rhs) const;

    bool operator!=(const Planet &rhs) const;
};

std::ostream &operator<<(std::ostream &os, const sf::Vector2f &vector);