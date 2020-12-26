#pragma once

#define PI 3.14159265
#define DEG2RAD(x) ((x)*PI/180)
#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 1200
#define CENTER sf::Vector2f{WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2}


#define LOG_DEBUG(x) do { std::cout << "[DEBUG] " << __FILE__ << ":" << __LINE__ << ":" << __func__ << "() " << x << std::endl; } while (0);

#define LOG_ERROR(x) do { std::cerr << "[ERROR] " << __FILE__ << ":" << __LINE__ << ":" << __func__ << "() " << x << std::endl; } while (0);

#define LOG_WARNING(x) do { std::cerr << "[WARNING] " << __FILE__ << ":" << __LINE__ << ":" << __func__ << "() " << x << std::endl; } while (0);

#define LOG_INFO(x) do { std::cout << "[INFO] " << __FILE__ << ":" << __LINE__ << ":" << __func__ << "() " << x << std::endl; } while (0);