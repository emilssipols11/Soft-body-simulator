//
// Created by leo on 4/20/21.
//
#include "MPoint.h"
#include <functional>

#ifndef SOFT_BODY_SIMULATOR_SPRING_H
#define SOFT_BODY_SIMULATOR_SPRING_H

class Spring{
public:
    //Constructor setting all the variables of the class
    //the actual length of the spring must be specified separately
    // - it is set to l0 in the constructor
    Spring(const double& k, const double& damping, const double& l0);

    //default constructor initializes A and B
    Spring(){
        this->A = nullptr;
        this->B = nullptr;
    }

    //get the distance between the two mass points
    double gLen() const;


    void sA( MPoint* a);
    void sB( MPoint* b);
    double gK() const;
    double gl0() const;


    //calculate force from A's position and B's position
    //watch out with const
    //THIS ONE COMPUTES ONLY FOR A
    lmh::Vector2f compute_force() ;

    MPoint* gA() const;
    MPoint* gB() const;

private:

    //rigidness and damping
    double k;
    double damping;

    //returns the function that needs to be solved


    //default length (without any force applied)
    double l0;

    //every spring have two mass points
    MPoint* A;
    MPoint* B;
};

#endif //SOFT_BODY_SIMULATOR_SPRING_H
