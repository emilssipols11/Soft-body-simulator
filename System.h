//
// Created by leo on 4/28/21.
//

#ifndef SOFT_BODY_SIMULATOR_SYSTEM_H
#define SOFT_BODY_SIMULATOR_SYSTEM_H
#include "Dipole.h"

class System{
public:
    // Constructor setting all the variables of the class
    // dip - the Dipole
    System(const Dipole& dip);


    void simulate();

private:
    // the dipole
    Dipole dip;
    std::array<lmh::Vector2f, 2> comp_next( lmh::Vector2f& prev_pos, lmh::Vector2f& prev_vel);



};



#endif //SOFT_BODY_SIMULATOR_SYSTEM_H
