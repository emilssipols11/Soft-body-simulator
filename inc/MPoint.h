//
// Created by leo on 4/20/21.
//


#ifndef SOFT_BODY_SIMULATOR_MPOINT_H
#define SOFT_BODY_SIMULATOR_MPOINT_H
#include "Vector2f.h"
#include <vector>
#include <array>

class Spring;

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
    void sDamp(const double damp){
        this->damping = damp;
    }
    double gDamp() const {
        return this->damping;
    }


    lmh::Vector2f gPos() const;
    lmh::Vector2f gVel() const;
    lmh::Vector2f gForce();
    lmh::Vector2f gForce(const lmh::Vector2f& dx, const lmh::Vector2f& dv) ;
    double gMass() const;

    //set the attached springs to a masspoint
    void attach_spring(Spring& s);
    std::array<lmh::Vector2f, 2> comp_next(const int&);
    std::array<lmh::Vector2f, 2> comp_nextv2(const int&);


private:
    //vector of attached
    std::vector<Spring> attached;
    lmh::Vector2f position;
    lmh::Vector2f velocity;
    lmh::Vector2f force;
    double mass{};
    double damping;

    lmh::Vector2f diffeq(const lmh::Vector2f& target_pos, const lmh::Vector2f& current_pos, const lmh::Vector2f& target_vel ,const lmh::Vector2f& current_vel, const int& index) const;

};

#endif //SOFT_BODY_SIMULATOR_MPOINT_H
