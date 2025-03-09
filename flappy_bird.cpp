#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>

// Constantes du jeu
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const float GRAVITY = 0.5f;
const float JUMP_STRENGTH = -10.f;
const float ASTEROID_SPEED = 5.f;

class FlappyBird {
public:
    sf::RectangleShape shape;
    sf::Vector2f velocity;

    FlappyBird() {
        shape.setSize({40, 40});
        shape.setFillColor(sf::Color::Yellow);
        shape.setPosition(100, WINDOW_HEIGHT / 2);
    }

    void update() {
        velocity.y += GRAVITY;
        shape.move(0, velocity.y);

        // Empêche Flappy de sortir de l'écran
        if (shape.getPosition().y < 0)
            shape.setPosition(100, 0);
        if (shape.getPosition().y > WINDOW_HEIGHT - shape.getSize().y)
            shape.setPosition(100, WINDOW_HEIGHT - shape.getSize().y);
    }

    void jump() {
        velocity.y = JUMP_STRENGTH;
    }
};

class Asteroid {
public:
    sf::RectangleShape shape;

    Asteroid(float x, float y) {
        shape.setSize({40, 40});
        shape.setFillColor(sf::Color::Red);
        shape.setPosition(x, y);
    }

    void update() {
        shape.move(-ASTEROID_SPEED, 0);
    }
};

int main() {
    srand(time(0));
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Flappy Bird - C++ SFML");
    window.setFramerateLimit(60);

    FlappyBird flappy;
    std::vector<Asteroid> asteroids;
    sf::Clock asteroidSpawnClock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
                flappy.jump();
        }

        // Ajouter des astéroïdes toutes les 2 secondes
        if (asteroidSpawnClock.getElapsedTime().asSeconds() > 2) {
            float y = rand() % (WINDOW_HEIGHT - 40);
            asteroids.emplace_back(WINDOW_WIDTH, y);
            asteroidSpawnClock.restart();
        }

        flappy.update();
        for (auto &asteroid : asteroids)
            asteroid.update();

        // Nettoyer les astéroïdes hors écran
        asteroids.erase(std::remove_if(asteroids.begin(), asteroids.end(), [](Asteroid &a) {
            return a.shape.getPosition().x < -40;
        }), asteroids.end());

        window.clear();
        window.draw(flappy.shape);
        for (auto &asteroid : asteroids)
            window.draw(asteroid.shape);
        window.display();
    }

    return 0;
}
