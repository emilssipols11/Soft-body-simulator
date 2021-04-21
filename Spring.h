//
// Created by leo on 4/20/21.
//
#include "MPoint.h"

#ifndef SOFT_BODY_SIMULATOR_SPRING_H
#define SOFT_BODY_SIMULATOR_SPRING_H

class Spring{
public:
    //Constructor setting all the variables of the class
    //the actual length of the spring must be specified separately
    // - it is set to l0 in the constructor
    Spring(const double& k, const double& damping, const double& l0);


    //get the distance between the two mass points
    double gLen() const;

    void sA(const MPoint& a);
    void sB(const MPoint& b);

    //calculate force from A's position and B's position
    //watch out with const
    //THIS ONE COMPUTES ONLY FOR A
    lmh::Vector2f compute_force() ;

private:

    //rigidness and damping
    double k;
    double damping;

    //default length (without any force applied)
    double l0;

    //every spring have two mass points
    MPoint A;
    MPoint B;


};

#endif //SOFT_BODY_SIMULATOR_SPRING_H
