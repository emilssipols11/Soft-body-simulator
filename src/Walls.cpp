#include "Walls.h"
#include "iostream"

Walls::Walls(sf::RenderWindow &w) {

    wall_lines.resize(5);
    /*
    vertices[0] = sf::Vector2f(0,0); // top left
    vertices[1] = sf::Vector2f (w->getSize().x, 0); // top right
    vertices[2] = sf::Vector2f(0, w->getSize().y);  //bottom left
    vertices[3] = sf::Vector2f(w->getSize().x, w->getSize().y); //bottom right
    */
    //wall_lines.resize(4);

    this->w = &w;

    wall_lines.setPrimitiveType(sf::LineStrip);



}

Walls::Walls(sf::RenderWindow *w, const int offset) {

    vertices[0] = sf::Vector2f(0 + offset,0 + offset); // top left
    vertices[1] = sf::Vector2f (w->getSize().x - offset, 0 + offset); // top right
    vertices[2] = sf::Vector2f(0 + offset, w->getSize().y - offset);  //bottom left
    vertices[3] = sf::Vector2f(w->getSize().x - offset, w->getSize().y - offset); //bottom right


    wall_lines.setPrimitiveType(sf::LineStrip);

    wall_lines.resize(4);
}



Walls::Walls(const std::array<sf::Vector2f, 4>& v) {


}

void Walls::draw_walls(double offset) {

    this->offset = offset;

    vertices[0] = sf::Vector2f(0 + offset,0 + offset); // top left
    vertices[1] = sf::Vector2f (w->getSize().x - offset, 0 + offset); // top right
    vertices[2] = sf::Vector2f(w->getSize().x - offset, w->getSize().y - offset);  //bottom left
    vertices[3] = sf::Vector2f( offset, w->getSize().y - offset); //bottom right

    wall_lines[0].position = vertices[0];
    wall_lines[1].position = vertices[1];
    wall_lines[2].position = vertices[2];
    wall_lines[3].position = vertices[3];
    wall_lines[4].position = vertices[0];
    w->draw(wall_lines);
}

