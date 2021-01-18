#pragma once

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <ostream>
#include <random>
#include <chrono>
#include <iostream>
#include  <iterator>

#define PI 3.14159265
#define DEG2RAD(x) ((x)*PI/180)
#define RAD2DEG(x) ((x)*180/PI)
#define WINDOW_WIDTH 1500
#define WINDOW_HEIGHT 1500
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

class FPS {
public:
    FPS() : mFrame(0), mFps(0) {}

    [[nodiscard]] unsigned int getFPS() const { return mFps; }

private:
    unsigned int mFrame;
    unsigned int mFps;
    sf::Clock mClock;

public:
    void update() {
        if (mClock.getElapsedTime().asSeconds() >= 1.f) {
            mFps = mFrame;
            mFrame = 0;
            mClock.restart();
        }

        ++mFrame;
    }
};

template<typename Iter, typename RandomGenerator>
Iter select_randomly(Iter start, Iter end, RandomGenerator& g) {
    std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
    std::advance(start, dis(g));
    return start;
}

template<typename Iter>
Iter select_randomly(Iter start, Iter end) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return select_randomly(start, end, gen);
}

fpt sfAbs(const sf::Vector2<fpt> &vec);

std::ostream &operator<<(std::ostream &os, const sf::Vector2<fpt> &vector);

sf::Vector2<fpt> operator+(const sf::Vector2<fpt> &lhs, fpt scalar);

sf::Vector2<fpt> operator-(const sf::Vector2<fpt> &lhs, fpt scalar);

sf::Vector2<fpt> operator/(const sf::Vector2<fpt> &lhs, fpt scalar);

sf::Vector2<fpt> operator*(const sf::Vector2<fpt> &lhs, fpt scalar);