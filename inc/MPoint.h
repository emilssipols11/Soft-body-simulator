//
// Created by leo on 4/20/21.
//
#include "Vector2f.h"
#include <vector>
#include <array>
#include <SFML/Graphics.hpp>
#include "Obstacle.h"

#ifndef SOFT_BODY_SIMULATOR_MPOINT_H
#define SOFT_BODY_SIMULATOR_MPOINT_H

class System;
class Spring;

class MPoint{

public:
    //constructor takes all the parameters using the constructor
    MPoint(lmh::Vector2f  pos, lmh::Vector2f  vel, lmh::Vector2f  force, const double& m, const double &d=0.0);

    //default constructor
    MPoint() = default;

    /*
     * GETTERS AND SETTERS
     * */
    void sPos(const lmh::Vector2f& pos );
    void sVel(const lmh::Vector2f& vel);
    void sForce(const lmh::Vector2f& force);
    void sDamp(const double damp){
        this->damping = damp;
    }
    double gDamp() const {
        return this->damping;
    }

    lmh::Vector2f gPos() const;
    lmh::Vector2f gVel() const;
    lmh::Vector2f gForce();
    double gMass() const;

    //set the attached springs to a masspoint
    void attach_spring(Spring& s);

    //we set the specs for the circle that will be drawed
    void sDrawable();
    void draw(sf::RenderWindow* w) ;
    lmh::Vector2f diffeq(const lmh::Vector2f& target_pos, const lmh::Vector2f& current_pos, const lmh::Vector2f& target_vel ,const lmh::Vector2f& current_vel, const int& index) const;
    inline double gR(){return this->circle.getRadius(); };
    void sR(const float &r){ this->circle.setRadius(r); };

    double get_distance(const Obstacle& obst);
    double get_elasticity() const;
    double sElasticity(const double&);
    static double GRAVITY;


private:
    //vector of attached
    std::vector<Spring> attached;
    lmh::Vector2f position;
    lmh::Vector2f velocity;
    lmh::Vector2f force;
    double mass{};
    double damping;
    sf::CircleShape circle;
    double elasticity = 1.0;

    //absolute value function for double...
    inline double abs(const double &d){
        return (d>=0 ? d : -d);
    }




};


#endif //SOFT_BODY_SIMULATOR_MPOINT_H
