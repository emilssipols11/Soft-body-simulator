//
// Created by leo on 4/28/21.
//

#include "System.h"

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

