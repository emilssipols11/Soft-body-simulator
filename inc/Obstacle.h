#ifndef SOFT_BODY_SIMULATOR_OBSTACLE_H
#define SOFT_BODY_SIMULATOR_OBSTACLE_H
#include "Vector2f.h"
#include <SFML/Graphics.hpp>

/*the obstacle in our case is just a
 * line segment consisting of two Vector2f -
 * one is for the origin of the line segment
 * and the other is the segment itself
 */



struct Obstacle{

    Obstacle(const double& a, const double& b, const double& c,const double &d): origin(a,b), vector(c,d){
        lines.resize(2);
        lines.setPrimitiveType(sf::LineStrip);
    };
    void draw(sf::RenderWindow&);


    lmh::Vector2f origin;
    lmh::Vector2f vector;
    sf::VertexArray lines;

};

#endif //SOFT_BODY_SIMULATOR_OBSTACLE_H
