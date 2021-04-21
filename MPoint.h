//
// Created by leo on 4/20/21.
//
#include "Vector2f.h"

#ifndef SOFT_BODY_SIMULATOR_MPOINT_H
#define SOFT_BODY_SIMULATOR_MPOINT_H


class MPoint{

public:
    //constructor takes all the parameters using the constructor
    MPoint(lmh::Vector2f  pos, lmh::Vector2f  vel, lmh::Vector2f  force, const double& m);

    //default constructor
    MPoint() = default;

    /*
     * GETTERS AND SETTERS
     * */
    void sPos(const lmh::Vector2f& pos );
    void sVel(const lmh::Vector2f& vel);
    void sForce(const lmh::Vector2f& force);

    lmh::Vector2f gPos() const;
    lmh::Vector2f gVel() const;
    lmh::Vector2f gForce() const;


private:
    lmh::Vector2f position;
    lmh::Vector2f velocity;
    lmh::Vector2f force;
    double mass{};

};

#endif //SOFT_BODY_SIMULATOR_MPOINT_H
