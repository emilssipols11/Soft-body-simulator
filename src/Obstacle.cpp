#include "Obstacle.h"

void Obstacle::draw(sf::RenderWindow &w) {
    lines[0].position = sf::Vector2f(this->origin.gX(), this->origin.gY());
    lines[1].position = sf::Vector2f(this->vector.gX() + this->origin.gX(),this->origin.gY()+ this->vector.gY());
    w.draw(lines);
}

