#include "../include/Asteroid.hpp"

Asteroid::Asteroid(float x, float y) {
    if (!texture.loadFromFile("asteroid.png")) {
        throw std::runtime_error("Failed to load asteroid.png");
    }
    sprite.setTexture(texture);
    sprite.setScale(0.1f, 0.1f);
    sprite.setPosition(x, y);
}

void Asteroid::update() {
    sprite.move(-SPEED, 0);
}

sf::FloatRect Asteroid::getBounds() {
    return sprite.getGlobalBounds();
}
