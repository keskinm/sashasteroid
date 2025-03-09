#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Asteroid.hpp"

class Laser {
public:
    Laser(sf::Vector2f start, float angle);
    void update(std::vector<Asteroid>& asteroids);
    sf::VertexArray& getBeam() { return beam; }

private:
    sf::VertexArray beam;
    sf::Vector2f origin;
    sf::Vector2f direction;
    static constexpr float LENGTH = 300.f;
};
