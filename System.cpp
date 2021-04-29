//
// Created by leo on 4/28/21.
//

#include "System.h"
#include <fstream>


System::System(const Dipole &dip) : dip(dip) {

}

std::array<lmh::Vector2f, 2> System::comp_next(lmh::Vector2f& prev_pos, lmh::Vector2f& prev_vel) {

    lmh::Vector2f dx1, dx2, dx3, dx4, dv1, dv2, dv3, dv4;
    double h = 0.05;

    dx1 = prev_vel*h;
    dv1 = (this->dip.diffeq)(prev_pos, prev_vel)*h;

    dx2 = (prev_vel + dv1*0.5)*h;
    dv2 = (this->dip.diffeq)(prev_pos+dx1*0.5, prev_vel + dv1*0.5 )*h;

    dx3 = (prev_vel + dv2*0.5)*h;
    dv3 = (this->dip.diffeq)(prev_pos + dx2*0.5, prev_vel + dv1*0.5)*h;

    dx4 = (prev_vel + dv3)*h;
    dv4 = (this->dip.diffeq)(prev_pos + dx3, prev_vel + dv1)*h;

    lmh::Vector2f dv = (dv1 + dv2*0.5 + dv3*0.5 + dv4)*(1.0/6.0);
    lmh::Vector2f dx = (dx1 + dx2*0.5 + dx3*0.5 + dx4)*(1.0/6.0);


    return std::array<lmh::Vector2f, 2> { prev_pos + dx , prev_vel + dv};
}



void System::simulate(const double& max_time) {
    double time = 0.0;
    this->data.at(0).push_back(dip.gA().gPos());
    this->data.at(1).push_back(dip.gA().gVel());

    int n = 0;

    std::array<lmh::Vector2f, 2> temp;

    while (time<max_time){
        //evaluate the expression after dt
        temp = this->comp_next(this->data.at(0)[n], this->data.at(1)[n]);

        //update the position of the dipole
        this->dip.sA(MPoint(temp[0], temp[1], lmh::Vector2f(0.0, 0.0), dip.gA().gMass()));

        this->data[0].push_back(temp[0]);
        this->data[1].push_back(temp[1]);

        n++;

        time+=dt;
    }


}

void System::write_to_file() {
    std::ofstream file("../system.txt");
    for(int i =0; i<this->data[0].size(); i++){
        file<<this->data[0].at(i).gX() <<"\t"<<this->data[0].at(i).gY()<<"\n";
    }

    file.close();
}

