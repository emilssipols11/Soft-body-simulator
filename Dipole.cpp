//
// Created by leokr on 4/22/2021.
//
#include "Dipole.h"
#include <vector>
#include <fstream>

Dipole::Dipole(const MPoint &a, const MPoint &b, const Spring &s) : A(a), B(b), spr(s) {

}


void Dipole::simulate_euler() {


    double t = 0;
    double dt = 0.005;
    double t_end = 10.0;

    this->spr.sA(A);
    this->spr.sB(B);

    std::vector<lmh::Vector2f> pos;
    std::vector<lmh::Vector2f> vel;
    std::vector<lmh::Vector2f> force;
    //set initial condition

    pos.push_back(A.gPos());
    vel.push_back(A.gVel());

    // v_n+1 = v_n + (F)/m * dt

    //pos.push_back(attached.)

    lmh::Vector2f temp;
    int iter = 0;

    while(t<t_end){
        temp = spr.compute_force();
        force.push_back(temp);

        A.sForce(temp);
        //compute the velocity at the next frame
        vel.push_back( vel[iter] + (A.gForce())*(1/A.gMass())*dt );

        //compute the position
        pos.push_back( pos[iter] + vel[iter]*dt);

        //
        A.sPos(pos[++iter]);
        spr.sA(&A);
        t+=dt;
    }

    std::ofstream file("../pos.txt");



    for(int x = 0; x<pos.size(); x++){
        std::cout<< "position : " << pos[x];
        std::cout <<"velocity"<< vel[x];
        //std::cout <<"force"<< force[x] << std::endl;
        file<<pos[x].gY()<<"\n";

    }
    file.close();
}


void Dipole::sA(const MPoint & a) {
    this->A = a;
}

void Dipole::sB(const MPoint & b) {
    this->B = b;
}

