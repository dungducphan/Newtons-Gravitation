#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include "utils.hpp"


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

int main() {
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Newton's gravitation", sf::Style::Default);
    window.setFramerateLimit(60);
    sf::Event event;
    std::default_random_engine engine(NOW);
    std::uniform_real_distribution<fpt> red_dist(200, 255);
    std::uniform_real_distribution<fpt> green_dist(200, 255);
    std::uniform_real_distribution<fpt> blue_dist(200, 255);
    std::uniform_real_distribution<fpt> alpha_dist(100, 150);
    std::vector<Planet> planets;

    sf::Font font;
    if (!font.loadFromFile("DejaVuSans.ttf")) {
        LOG_ERROR("Can not load DejaVuSans.ttf. Exit");
        std::exit(1);
    }

    planets.emplace_back(sf::Vector2<fpt>(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), 1000000000,
                         sf::Vector2<fpt>(0.f, -0.005),
                         sf::Color(200, 32, 125, 200), 50);
    planets.back().isStar = true;


    float deltaT = 0.f;
    float speed = 10000.0f;
    FPS fps;

    sf::Clock frameClock;
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
            if (event.type == sf::Event::EventType::MouseWheelMoved) {
                fpt scrolled = event.mouseWheel.delta;
                speed += scrolled * 100.0f;
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

        // Update position
        for (int i = 0; i < deltaVs.size(); i++) {
            if (!planets[i].isStar) {
                planets[i].v += deltaVs[i];
                sf::Vector2<fpt> deltaS = planets[i].v * deltaT;
                planets[i].p += deltaS;
            }
        }

        // Collision detection
        for (auto i = planets.begin(); i != planets.end();) {
            bool collision = false;
            auto j = i + 1;
            for (; j != planets.end();) {
                if (*i != *j) {
                    sf::Vector2<fpt> direction = i->p - j->p;
                    fpt distance = sfAbs(direction);
                    if (distance < 30) {
                        collision = true;
                        break;
                    } else {
                        j++;
                    }
                }
            }
            if (collision) {
                if (j->isStar) {
                    j->m += i->m;
                    i = planets.erase(i);
                } else {
                    i->m += j->m;
                    planets.erase(j);
                    i++;
                }
            } else {
                i++;
            }
        }

        window.clear(sf::Color::Black);
        for (auto &planet : planets) {
            planet.draw(window);
        }


        std::stringstream ss;
        ss << "Speed: " << (int) speed;
        sf::Text speedText{ss.str(), font, 10};
        speedText.setPosition(10, 10);
        speedText.setFillColor(sf::Color::White);
        window.draw(speedText);


        ss = std::stringstream{};
        fps.update();
        ss << "FPS: " << fps.getFPS();
        sf::Text fpsText{ss.str(), font, 10};
        fpsText.setPosition(10, 25);
        fpsText.setFillColor(sf::Color::White);
        window.draw(fpsText);

        window.display();
        deltaT = clock.restart().asSeconds() * speed;
    }

    return 0;
}
