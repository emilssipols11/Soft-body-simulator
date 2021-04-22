//
// Created by leokr on 4/22/2021.
//
#include "Spring.h"
#ifndef SOFT_BODY_SIMULATOR_DIPOLE_H
#define SOFT_BODY_SIMULATOR_DIPOLE_H
class Dipole{
public:
    Dipole(const MPoint& a, const MPoint& b, const Spring& s);


    MPoint gA() const;
    MPoint gB() const;

    void sA(const MPoint&);
    void sB(const MPoint&);

    void simulate_euler();


private:
    MPoint A;
    MPoint B;
    Spring spr;

};

#endif //SOFT_BODY_SIMULATOR_DIPOLE_H
