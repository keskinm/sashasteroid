#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <cmath>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const float GRAVITY = 0.5f;
const float JUMP_STRENGTH = -10.f;
const float ASTEROID_SPEED = 5.f;
const int NUM_LASERS = 5;
const float LASER_LENGTH = 300.f;
const float LASER_ANGLE_STEP = M_PI / (NUM_LASERS - 1);

class FlappyBird {
public:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f velocity;

    FlappyBird() {
        if (!texture.loadFromFile("flappy.png")) {
            throw std::runtime_error("Failed to load flappy.png");
        }
        sprite.setTexture(texture);
        sprite.setScale(0.1f, 0.1f);
        sprite.setPosition(100, WINDOW_HEIGHT / 2);
    }

    void update() {
        velocity.y += GRAVITY;
        sprite.move(0, velocity.y);
        if (sprite.getPosition().y < 0)
            sprite.setPosition(100, 0);
        if (sprite.getPosition().y > WINDOW_HEIGHT - sprite.getGlobalBounds().height)
            sprite.setPosition(100, WINDOW_HEIGHT - sprite.getGlobalBounds().height);
    }

    void jump() {
        velocity.y = JUMP_STRENGTH;
    }

    sf::FloatRect getBounds() {
        return sprite.getGlobalBounds();
    }
};

class Asteroid {
public:
    sf::Sprite sprite;
    sf::Texture texture;

    Asteroid(float x, float y) {
        if (!texture.loadFromFile("asteroid.png")) {
            throw std::runtime_error("Failed to load asteroid.png");
        }
        sprite.setTexture(texture);
        sprite.setScale(0.1f, 0.1f);
        sprite.setPosition(x, y);
    }

    void update() {
        sprite.move(-ASTEROID_SPEED, 0);
    }

    sf::FloatRect getBounds() {
        return sprite.getGlobalBounds();
    }
};

class Laser {
public:
    sf::VertexArray beam;
    sf::Vector2f origin;
    sf::Vector2f direction;

    Laser(sf::Vector2f start, float angle) {
        origin = start;
        direction = sf::Vector2f(std::cos(angle), std::sin(angle));
        beam = sf::VertexArray(sf::Lines, 2);
        beam[0].position = origin;
        beam[0].color = sf::Color::Cyan;
        beam[1].position = origin + direction * LASER_LENGTH;
        beam[1].color = sf::Color::Cyan;
    }

    void update(std::vector<Asteroid> &asteroids) {
        float closestDistance = LASER_LENGTH;
        for (auto &asteroid : asteroids) {
            if (asteroid.getBounds().intersects(sf::FloatRect(beam[0].position, sf::Vector2f(1, 1)))) {
                float distance = std::hypot(asteroid.sprite.getPosition().x - origin.x, asteroid.sprite.getPosition().y - origin.y);
                if (distance < closestDistance) {
                    closestDistance = distance;
                }
            }
        }
        beam[1].position = origin + direction * closestDistance;
    }
};

bool checkCollision(FlappyBird &flappy, Asteroid &asteroid) {
    return flappy.getBounds().intersects(asteroid.getBounds());
}

int main() {
    srand(time(0));
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Flappy Bird - C++ SFML");
    window.setFramerateLimit(60);

    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("background.png")) {
        throw std::runtime_error("Failed to load background.png");
    }
    sf::Sprite background(backgroundTexture);
    background.setScale((float)WINDOW_WIDTH / backgroundTexture.getSize().x, (float)WINDOW_HEIGHT / backgroundTexture.getSize().y);

    FlappyBird flappy;
    std::vector<Asteroid> asteroids;
    std::vector<Laser> lasers;
    sf::Clock asteroidSpawnClock;
    bool gameOver = false;
    int score = 0;

    sf::Font font;
    if (!font.loadFromFile("arial.ttf")) {
        return -1;
    }

    sf::Text scoreText;
    scoreText.setFont(font);
    scoreText.setCharacterSize(30);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (!gameOver && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
                flappy.jump();
        }

        if (!gameOver) {
            if (asteroidSpawnClock.getElapsedTime().asSeconds() > 2) {
                float y = rand() % (WINDOW_HEIGHT - 40);
                asteroids.emplace_back(WINDOW_WIDTH, y);
                asteroidSpawnClock.restart();
            }

            flappy.update();
            for (auto &asteroid : asteroids)
                asteroid.update();

            lasers.clear();
            for (int i = 0; i < NUM_LASERS; i++) {
                float angle = -M_PI / 6 + i * LASER_ANGLE_STEP;
                lasers.emplace_back(flappy.sprite.getPosition() + sf::Vector2f(20, 20), angle);
            }
            for (auto &laser : lasers)
                laser.update(asteroids);

            for (auto &asteroid : asteroids) {
                if (checkCollision(flappy, asteroid)) {
                    gameOver = true;
                }
            }
        }

        window.clear();
        window.draw(background);
        window.draw(flappy.sprite);
        for (auto &asteroid : asteroids)
            window.draw(asteroid.sprite);
        for (auto &laser : lasers)
            window.draw(laser.beam);
        window.draw(scoreText);

        if (gameOver) {
            sf::Text gameOverText("Game Over", font, 50);
            gameOverText.setFillColor(sf::Color::White);
            gameOverText.setPosition(WINDOW_WIDTH / 2 - 100, WINDOW_HEIGHT / 2 - 25);
            window.draw(gameOverText);
        }

        window.display();
    }

    return 0;
}
