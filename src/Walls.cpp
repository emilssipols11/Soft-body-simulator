#include "Walls.h"

Walls::Walls(sf::RenderWindow *w) {
    vertices[0] = sf::Vector2f(0,0); // top left
    vertices[1] = sf::Vector2f (w->getSize().x, 0); // top right
    vertices[2] = sf::Vector2f(0, w->getSize().y);  //bottom left
    vertices[3] = sf::Vector2f(w->getSize().x, w->getSize().y); //bottom right
}

Walls::Walls(const std::array<sf::Vector2f, 4>& v) {



}




