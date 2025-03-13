#pragma once
#include <SFML/Graphics.hpp>
#include "FlappyBird.hpp"
#include "Asteroid.hpp"
#include "Laser.hpp"
#include <cmath>


class GameManager {
public:
    GameManager();
    void run();

private:
    void processEvents();
    void update();
    void render();
    void spawnAsteroid();
    void updateLasers();
    bool checkCollisions();

    sf::RenderWindow window;
    sf::Sprite background;
    sf::Texture backgroundTexture;
    sf::Font font;
    sf::Text scoreText;
    sf::Text gameOverText;

    FlappyBird flappy;
    std::vector<Asteroid> asteroids;
    std::vector<Laser> lasers;
    sf::Clock asteroidSpawnClock;
    bool gameOver;
    int score;

    static constexpr int WINDOW_WIDTH = 800;
    static constexpr int WINDOW_HEIGHT = 600;
    static constexpr int NUM_LASERS = 8;
    static constexpr float LASER_ANGLE_STEP = M_PI / (NUM_LASERS + 1);
};
