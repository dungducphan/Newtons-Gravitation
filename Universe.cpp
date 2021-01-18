#include "Universe.hpp"

Universe::Universe(sf::RenderWindow *window, sf::Font *font) : window(window), font(font) {
    if (!sunTexture.loadFromFile("sun.png", sf::IntRect(0, 0, 660, 660))) {
        LOG_ERROR("Can not load sun.png. Exit now")
        std::exit(1);
    }

    // Load planet images
    constexpr int32_t height = 2985;
    constexpr int32_t width = 6927;
    constexpr int32_t rows = 3;
    constexpr int32_t cols = 7;
    constexpr int32_t sprite_width = width / cols;
    constexpr int32_t sprite_height = height / rows;
    sf::Image planet;
    if(!planet.loadFromFile("planets.png")) {
        LOG_ERROR("Can not load planets.png. Exit now")
        std::exit(1);
    }
    for (int32_t y = 0; y < rows; y++) {
        for (int32_t x = 0; x < cols; x++) {
            sf::Texture texture;
            sf::Image subImage;
            subImage.create(sprite_width, sprite_height);
            subImage.copy(planet, 0, 0, sf::IntRect{x * sprite_width, y * sprite_height, sprite_width, sprite_height});
            texture.loadFromImage(subImage);
            planetTextures.push_back(texture);
        }
    }

    // Create the sun
    planets.emplace_back(sf::Vector2<fpt>(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2), 2500000000,
                         sf::Vector2<fpt>(0.f, -0.005),
                         sf::Color(200, 32, 125, 200), 100, sunTexture);

    planets.back().isStar = true;
}

void Universe::simulate() {
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
                if (distance < i->r / 2 || distance < j->r / 2) {
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
}


void Universe::infoText() {
    std::stringstream ss;
    ss << "Speed: " << (int) speed;
    sf::Text speedText{ss.str(), *font, 10};
    speedText.setPosition(10, 10);
    speedText.setFillColor(sf::Color::White);
    window->draw(speedText);

    ss = std::stringstream{};
    fps.update();
    ss << "FPS: " << fps.getFPS();
    sf::Text fpsText{ss.str(), *font, 10};
    fpsText.setPosition(10, 25);
    fpsText.setFillColor(sf::Color::White);
    window->draw(fpsText);
}


void Universe::run() {
    while (window->isOpen()) {
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::EventType::Closed) {
                std::exit(0);
            }
            if (event.type == sf::Event::EventType::MouseButtonPressed) {
                fpt x = event.mouseButton.x;
                fpt y = event.mouseButton.y;
                Planet planet(sf::Vector2<fpt>(x, y), 1000, sf::Vector2<fpt>(0.01f, -0.01),
                              sf::Color(red_dist(engine),
                                        green_dist(engine),
                                        blue_dist(engine),
                                        alpha_dist(engine)),
                              50, *select_randomly(planetTextures.begin(), planetTextures.end()));

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

        simulate();

        window->clear(sf::Color::Black);
        for (auto &planet : planets) {
            planet.draw(*window);
        }

        infoText();

        window->display();
        deltaT = clock.restart().asSeconds() * speed;
    }
}