#include "../include/Laser.hpp"
#include <cmath>

Laser::Laser(sf::Vector2f start, float angle) {
    origin = start;
    direction = sf::Vector2f(std::cos(angle), std::sin(angle));
    beam = sf::VertexArray(sf::Lines, 2);
    beam[0].position = origin;
    beam[0].color = sf::Color::Cyan;
    beam[1].position = origin + direction * LENGTH;
    beam[1].color = sf::Color::Cyan;
}

void Laser::update(std::vector<Asteroid>& asteroids) {
    float closestDistance = LENGTH;
    for (auto& asteroid : asteroids) {
        if (asteroid.getBounds().intersects(sf::FloatRect(beam[0].position, sf::Vector2f(1, 1)))) {
            float distance = std::hypot(asteroid.getPosition().x - origin.x, 
                                     asteroid.getPosition().y - origin.y);
            if (distance < closestDistance) {
                closestDistance = distance;
            }
        }
    }
    beam[1].position = origin + direction * closestDistance;
}
