//
// Created by leo on 4/20/21.
//
#include "MPoint.h"

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

lmh::Vector2f MPoint::gForce() const {
    return this->force;
}

double MPoint::gMass() const {
    return this->mass;
}


