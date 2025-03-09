#include "../include/FlappyBird.hpp"

FlappyBird::FlappyBird() {
    if (!texture.loadFromFile("assets/flappy.png")) {
        throw std::runtime_error("Failed to load assets/flappy.png");
    }
    sprite.setTexture(texture);
    sprite.setScale(0.1f, 0.1f);
    sprite.setPosition(100, 600 / 2); // WINDOW_HEIGHT/2
}

void FlappyBird::update() {
    velocity.y += GRAVITY;
    sprite.move(0, velocity.y);
    
    if (sprite.getPosition().y < 0)
        sprite.setPosition(100, 0);
    if (sprite.getPosition().y > 600 - sprite.getGlobalBounds().height)
        sprite.setPosition(100, 600 - sprite.getGlobalBounds().height);
}

void FlappyBird::jump() {
    velocity.y = JUMP_STRENGTH;
}

sf::FloatRect FlappyBird::getBounds() {
    return sprite.getGlobalBounds();
}
