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

    this->spr.sA(&(this->A));
    this->spr.sB(&(this->B));

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

/*void Dipole::simulate_RK4() {


    double t = 0;
    double dt = 0.05;
    double t_end = 20;

    this->spr.sA(&(this->A));
    this->spr.sB(&(this->B));

    std::vector<double> pos;
    std::vector<double> vel;
    std::vector<lmh::Vector2f> force;

    pos.push_back(14.0);
    vel.push_back(0);

    F = [&](double x){

        return (10 - x);
    };

    lmh::Vector2f temp;
    int iter = 0;
    //double x;

    while (t<t_end) {

        pos.push_back(comp_next(pos, vel, iter)[0]);
        vel.push_back(comp_next(pos, vel, iter)[1]);

        iter++;
        t+=dt;


    }


    std::ofstream file("../eu.txt");

    for(int x = 0; x<pos.size(); x++){

        //std::cout <<"force"<< force[x] << std::endl;
        file<<pos[x]<<"\t"<<x*0.05<<"\n";

    }

    file.close();

}*/


void Dipole::sA(const MPoint & a) {
    this->A = a;
}

void Dipole::sB(const MPoint & b) {
    this->B = b;
}


lmh::Vector2f Dipole::diffeq(const lmh::Vector2f &,const lmh::Vector2f &) {
    //The force acting on A!
    //  a = k(lo - x)/M

    return lmh::Vector2f(
            ( this->gA().gPos()).normalize()*(this->spr.gl0() - lmh::Vector2f(this->gA().gPos() - this->B.gPos()).norm())*(this->spr.gK())
    );
}

MPoint Dipole::gA() const {
    return this->A;
}

MPoint Dipole::gB() const {
    return this->B;
}
