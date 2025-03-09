#pragma once
#include <SFML/Graphics.hpp>

class FlappyBird {
public:
    FlappyBird();
    void update();
    void jump();
    sf::FloatRect getBounds();
    sf::Sprite& getSprite() { return sprite; }
    sf::Vector2f getPosition() const { return sprite.getPosition(); }

private:
    sf::Sprite sprite;
    sf::Texture texture;
    sf::Vector2f velocity;
    static constexpr float GRAVITY = 0.5f;
    static constexpr float JUMP_STRENGTH = -10.f;
};
