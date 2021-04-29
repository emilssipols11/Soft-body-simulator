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


    void simulate(const double&max_time);
    void write_to_file();

private:
    // the dipole
    Dipole dip;

    //time increment
    double dt = 0.05;
    std::array<lmh::Vector2f, 2> comp_next( lmh::Vector2f& prev_pos, lmh::Vector2f& prev_vel);

    //tempoprary structure to store data (position and velocity)
    std::array<std::vector<lmh::Vector2f>, 2> data;



};



#endif //SOFT_BODY_SIMULATOR_SYSTEM_H
