//
// Created by leo on 4/20/21.
//
#include "MPoint.h"
#include "Spring.h"
#include "Dipole.h"
#include <utility>
#include <cmath>

MPoint::MPoint(lmh::Vector2f pos, lmh::Vector2f vel, lmh::Vector2f force, const double &m, const double &d)
    : position(pos), velocity(vel), force(force), mass(m), damping(d){
    this->circle.setOrigin(circle.getRadius()/2.0, circle.getRadius()/2.0);
}

void MPoint::sPos(const lmh::Vector2f &pos) {
    this->position = pos;
}

void MPoint::sVel(const lmh::Vector2f &vel) {
    this->velocity = vel;
}

void MPoint::sForce(const lmh::Vector2f &force) {
    this->force = force;
}

lmh::Vector2f MPoint::gPos() const {
    return this->position;
}

lmh::Vector2f MPoint::gVel() const {
    return this->velocity;
}


//accumulates the force on a particular mPoint
//taking into account all the other mPoints attached
// using the physics computed by the diffeq() funcction
lmh::Vector2f MPoint::gForce()  {
    //lmh::Vector2f temp_force(0.0, 0.0);
    this->force = (lmh::Vector2f(0.0, 0.0));
    for (int i = 0; i < attached.size(); ++i) {
        if(attached[i].gB() != this) {
            this->force+=diffeq(this->gPos(), attached[i].gB()->gPos(), this->gVel(), attached[i].gB()->gVel(), i);
        } else {
            this->force+=diffeq(this->gPos(), attached[i].gA()->gPos(), this->gVel(), attached[i].gA()->gVel(), i);

        }
    }
    return this->force;
}

double MPoint::gMass() const {

    return this->mass;
}

void MPoint::attach_spring(Spring& s) {
    this->attached.push_back(s);
}

lmh::Vector2f MPoint::diffeq(const lmh::Vector2f& target_pos, const lmh::Vector2f& current_pos, const lmh::Vector2f& target_vel ,const lmh::Vector2f& current_vel, const int& index) const {

    return lmh::Vector2f(
            ((target_pos-current_pos)*(this->attached[index].gl0()/(target_pos-current_pos).norm()) - (target_pos-current_pos))*this->attached[index].gK() - velocity*damping + lmh::Vector2f(800, 10000)

    );

}

void MPoint::draw(sf::RenderWindow *w) {

    this->circle.setOrigin(circle.getRadius()/2.0, circle.getRadius()/2.0);
    circle.setPosition(this->position.gX() - circle.getRadius()/2.0, this->position.gY() - circle.getRadius()/2.0);

    w->draw(this->circle);
}

void MPoint::sDrawable() {
}


double MPoint::get_distance(const Obstacle& obst){ // the integer is to know what mPoint we are checking
    /*
     * the line must be put in the form of ax + bx + c = 0
     * in order to compute the distance of a point to a line
     */
    //A = y_2 - y_1 , with y_2 = y_origin + y_vector & y_1 = y_origin ==> A = y_vector
    // B = x_1 - x_2 , ==> similarly, B = - x_vector
    //double C = obst.vector.gX() * obst.origin.gY() - obst.vector.gY() * obst.origin.gX();
    /*
     * the distance between a point and a line is given by
     * D = {abs(A*M_x + B*M_y + C )/ sqrt(A^2 + B^2)}
     */

    //consider removing the sqrt ...
    //std::cout<<abs(-3.2)<<std::endl;

    double A = obst.vector.gY();
    double B = -obst.vector.gX();
    double C = obst.vector.gX()*obst.origin.gY() - obst.vector.gY()*obst.origin.gX();

    double d = (abs(A*this->position.gX() + B*this->position.gY() + C))/(sqrt(A*A + B*B));
    //std::cout<<this<<"\t"<<d<<"\n";
    return d;

}
