#include "../include/GameManager.hpp"
#include <cstdlib>
#include <ctime>

GameManager::GameManager() : window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Flappy Bird - C++ SFML") {
    window.setFramerateLimit(60);
    srand(time(0));

    if (!backgroundTexture.loadFromFile("assets/background.png")) {
        throw std::runtime_error("Failed to load assets/background.png");
    }
    background.setTexture(backgroundTexture);
    background.setScale(
        (float)WINDOW_WIDTH / backgroundTexture.getSize().x,
        (float)WINDOW_HEIGHT / backgroundTexture.getSize().y
    );

    if (!font.loadFromFile("assets/arial.ttf")) {
        throw std::runtime_error("Failed to load assets/arial.ttf");
    }

    scoreText.setFont(font);
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);

    gameOverText.setFont(font);
    gameOverText.setString("Game Over");
    gameOverText.setCharacterSize(50);
    gameOverText.setFillColor(sf::Color::White);
    gameOverText.setPosition(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 - 25);

    gameOver = false;
    score = 0;
}

void GameManager::run() {
    while (window.isOpen()) {
        processEvents();
        if (!gameOver) {
            update();
        }
        render();
    }
}

void GameManager::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (!gameOver && event.type == sf::Event::KeyPressed && 
            event.key.code == sf::Keyboard::Space)
            flappy.jump();
    }
}

void GameManager::update() {
    if (asteroidSpawnClock.getElapsedTime().asSeconds() > 2) {
        spawnAsteroid();
    }

    flappy.update();
    
    for (auto& asteroid : asteroids) {
        asteroid.update();
    }

    updateLasers();
    
    if (checkCollisions()) {
        gameOver = true;
    }
}

void GameManager::render() {
    window.clear();
    window.draw(background);
    window.draw(flappy.getSprite());
    
    for (auto& asteroid : asteroids) {
        window.draw(asteroid.getSprite());
    }
    
    for (auto& laser : lasers) {
        window.draw(laser.getBeam());
    }
    
    window.draw(scoreText);

    if (gameOver) {
        window.draw(gameOverText);
    }

    window.display();
}

void GameManager::spawnAsteroid() {
    float y = rand() % (WINDOW_HEIGHT - 40);
    asteroids.emplace_back(WINDOW_WIDTH, y);
    asteroidSpawnClock.restart();
}

void GameManager::updateLasers() {
    lasers.clear();
    for (int i = 0; i < NUM_LASERS; i++) {
        float angle = -M_PI / 2 + i * LASER_ANGLE_STEP;
        lasers.emplace_back(flappy.getPosition() + sf::Vector2f(20, 20), angle);
    }
    for (auto& laser : lasers) {
        laser.update(asteroids);
    }
}

bool GameManager::checkCollisions() {
    for (auto& asteroid : asteroids) {
        if (flappy.getBounds().intersects(asteroid.getBounds())) {
            return true;
        }
    }
    return false;
}
