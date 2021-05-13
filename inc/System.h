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
    System();
    //we initialize the system


    //function that simulates the motion of a dipole till max_time
    //and stores it in the std::array<std::vector<lmh::Vector2f>, 2> data;
    void simulate(const double&max_time);

    //reads writes the     std::array<std::vector<lmh::Vector2f>, 2> data;
    //to a file "system.txt"
    void write_to_file();

    //DEPRECATED
    //std::array<lmh::Vector2f, 2> simulate_euler(const double& max_time);

    //delete the with "new" allocated MPoints* in the std::vector
    ~System();

private:
    // the dipole
    // Dipole dip;

    // the mass points
    std::vector<MPoint*> mPoints;

    //time increment
    double dt = 0.01;

    //the RK4 method that gives f(t+dt)
    //std::array<lmh::Vector2f, 2> comp_next(const int&);

    //temporary structure to store data (position and velocity)
    std::array<std::vector<lmh::Vector2f>, 2> data;



};



#endif //SOFT_BODY_SIMULATOR_SYSTEM_H
