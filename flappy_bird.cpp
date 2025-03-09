#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <sstream>

// Constantes du jeu
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const float GRAVITY = 0.5f;
const float JUMP_STRENGTH = -10.f;
const float ASTEROID_SPEED = 5.f;

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

        // Empêche Flappy de sortir de l'écran
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

bool checkCollision(FlappyBird &flappy, Asteroid &asteroid) {
    return flappy.getBounds().intersects(asteroid.getBounds());
}

int main() {
    srand(time(0));
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Flappy Bird - C++ SFML");
    window.setFramerateLimit(60);

    // Chargement du fond d'écran
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("background.png")) {
        throw std::runtime_error("Failed to load background.png");
    }
    sf::Sprite background(backgroundTexture);
    background.setScale((float)WINDOW_WIDTH / backgroundTexture.getSize().x, (float)WINDOW_HEIGHT / backgroundTexture.getSize().y);

    FlappyBird flappy;
    std::vector<Asteroid> asteroids;
    sf::Clock asteroidSpawnClock;
    bool gameOver = false;
    int score = 0;

    // Chargement de la police pour afficher le score
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
            // Ajouter des astéroïdes toutes les 2 secondes
            if (asteroidSpawnClock.getElapsedTime().asSeconds() > 2) {
                float y = rand() % (WINDOW_HEIGHT - 40);
                asteroids.emplace_back(WINDOW_WIDTH, y);
                asteroidSpawnClock.restart();
            }

            flappy.update();
            for (auto &asteroid : asteroids)
                asteroid.update();

            // Vérifier les collisions
            for (auto &asteroid : asteroids) {
                if (checkCollision(flappy, asteroid)) {
                    gameOver = true;
                }
            }

            // Supprimer les astéroïdes hors écran et augmenter le score
            asteroids.erase(std::remove_if(asteroids.begin(), asteroids.end(), [&](Asteroid &a) {
                if (a.sprite.getPosition().x < -40) {
                    score++;
                    return true;
                }
                return false;
            }), asteroids.end());
        }

        // Mettre à jour le texte du score
        std::stringstream ss;
        ss << "Score: " << score;
        scoreText.setString(ss.str());

        window.clear();
        window.draw(background);
        window.draw(flappy.sprite);
        for (auto &asteroid : asteroids)
            window.draw(asteroid.sprite);
        window.draw(scoreText);

        // Affichage du message "Game Over"
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
