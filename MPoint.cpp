//
// Created by leo on 4/20/21.
//
#include "MPoint.h"
#include "Spring.h"
#include "Dipole.h"
#include <utility>

MPoint::MPoint(lmh::Vector2f pos, lmh::Vector2f vel, lmh::Vector2f force, const double &m)
    : position(pos), velocity(vel), force(force), mass(m){
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
    //The force acting on A!
    //  a = k(lo - x)/M

    /*return lmh::Vector2f(
            ( this->gA().gPos()).normalize()*(this->spr.gl0() - lmh::Vector2f(this->gA().gPos() - this->B.gPos()).norm())*(this->spr.gK())
    );*/

    return lmh::Vector2f(
            ((target_pos-current_pos)*(this->attached[index].gl0()/(target_pos-current_pos).norm()) - (target_pos-current_pos))*this->attached[index].gK()
    );

}


