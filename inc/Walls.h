//
// Created by leo on 5/21/21.
//

#ifndef SOFT_BODY_SIMULATOR_WALLS_H
#define SOFT_BODY_SIMULATOR_WALLS_H
#include <array>
#include <SFML/Graphics.hpp>


class Walls{
public:
    Walls(sf::RenderWindow &w);
    Walls(sf::RenderWindow *w, const int offset);
    Walls(const std::array<sf::Vector2f, 4>& v);

    void draw_walls(double offset = 20);

    double gXl() const{ return vertices[0].x; };
    double gXr() const{ return vertices[1].x; };
    double gYu() const{ return vertices[0].y; };
    double gYd() const{ return vertices[2].y; };

private:

    double offset;

    //contains all the vertices
    std::array<sf::Vector2f, 4> vertices;
    sf::VertexArray wall_lines;
    sf::RenderWindow *w;

};


#endif //SOFT_BODY_SIMULATOR_WALLS_H
