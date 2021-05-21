//
// Created by leo on 5/21/21.
//

#ifndef SOFT_BODY_SIMULATOR_WALLS_H
#define SOFT_BODY_SIMULATOR_WALLS_H
#include <array>
#include <SFML/Graphics.hpp>


class Walls{
public:
    Walls(sf::RenderWindow *w);
    Walls(const std::array<sf::Vector2f, 4>& v);


private:

    //contains all the vertices
    std::array<sf::Vector2f, 4> vertices;
    sf::RenderWindow *w;

};


#endif //SOFT_BODY_SIMULATOR_WALLS_H
