#pragma once
#include <SFML/Graphics.hpp>

class Asteroid {
public:
    Asteroid(float x, float y);
    void update();
    sf::FloatRect getBounds();
    sf::Sprite& getSprite() { return sprite; }
    sf::Vector2f getPosition() const { return sprite.getPosition(); }

private:
    sf::Sprite sprite;
    sf::Texture texture;
    static constexpr float SPEED = 5.f;
};
