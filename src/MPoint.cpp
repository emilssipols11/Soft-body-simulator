//
// Created by leo on 4/20/21.
//
#include "MPoint.h"
#include "Spring.h"
#include "Dipole.h"
#include <utility>

MPoint::MPoint(lmh::Vector2f pos, lmh::Vector2f vel, lmh::Vector2f force, const double &m)
    : position(pos), velocity(vel), force(force), mass(m){
}

void MPoint::sPos(const lmh::Vector2f &pos) {
    this->position = pos;
}

void MPoint::sVel(const lmh::Vector2f &vel) {
    this->velocity = vel;
}

void MPoint::sForce(const lmh::Vector2f &force) {
    this->force = force;
}

lmh::Vector2f MPoint::gPos() const {
    return this->position;
}

lmh::Vector2f MPoint::gVel() const {
    return this->velocity;
}

lmh::Vector2f MPoint::gForce()  {
    //lmh::Vector2f temp_force(0.0, 0.0);
    this->force = (lmh::Vector2f(0.0, 0.0));
    for (int i = 0; i < attached.size(); ++i) {
        if(attached[i].gB() != this) {
            this->force+=diffeq(this->gPos(), attached[i].gB()->gPos(), this->gVel(), attached[i].gB()->gVel(), i);
        } else {
            this->force+=diffeq(this->gPos(), attached[i].gA()->gPos(), this->gVel(), attached[i].gA()->gVel(), i);

        }
    }
    return this->force;
}

lmh::Vector2f MPoint::gForce(const lmh::Vector2f& dx, const lmh::Vector2f& dv)  {
    //lmh::Vector2f temp_force(0.0, 0.0);
    this->force = (lmh::Vector2f(0.0, 0.0));
    for (int i = 0; i < attached.size(); ++i) {
        if(attached[i].gB() != this) {
            this->force+=diffeq(this->gPos()+dx, attached[i].gB()->gPos()-dx, this->gVel()+dv, attached[i].gB()->gVel()-dv, i);
        } else {
            this->force+=diffeq(this->gPos()+dx, attached[i].gA()->gPos()-dx, this->gVel()+dv, attached[i].gA()->gVel()-dv, i);

        }
    }
    return this->force;
}

std::array<lmh::Vector2f, 2> MPoint::comp_next(const int& i) {

    lmh::Vector2f dx1, dx2, dx3, dx4, dv1, dv2, dv3, dv4;
    double h = 0.01;



    //DX1 = mPoints[i].gForce

    dx1 = this->gVel()*h;

    //dv1 = mpoint.getForce()*(1/M)
    dv1 = (this->gForce())*h;

    dx2 = (this->gVel() + dv1*0.5)*h;
    dv2 = this->gForce(dx1*0.5, dv1*0.5)*h;

    dx3 = (this->gVel() + dv2*0.5)*h;
    dv3 = this->gForce(dx2*0.5, dv1*0.5)*h;

    dx4 = (this->gVel() + dv3)*h;
    dv4 = this->gForce( dx3,  dv1)*h;

    lmh::Vector2f dv = (dv1 + dv2*2.0+ dv3*2.0 + dv4)*(1.0/6.0);
    lmh::Vector2f dx = (dx1 + dx2*2.0 + dx3*2.0 + dx4)*(1.0/6.0);


    return std::array<lmh::Vector2f, 2> { this->gPos() + dx , this->gVel() + dv};
}

std::array<lmh::Vector2f, 2> MPoint::comp_nextv2(const int &) {

    lmh::Vector2f dx1 = lmh::Vector2f(0.0, 0.0);
    lmh::Vector2f dx2 = lmh::Vector2f(0.0, 0.0);
    lmh::Vector2f dx3 = lmh::Vector2f(0.0, 0.0);
    lmh::Vector2f dx4 = lmh::Vector2f(0.0, 0.0);
    lmh::Vector2f dv1 = lmh::Vector2f(0.0, 0.0);
    lmh::Vector2f dv2 = lmh::Vector2f(0.0, 0.0);
    lmh::Vector2f dv3 = lmh::Vector2f(0.0, 0.0);
    lmh::Vector2f dv4 = lmh::Vector2f(0.0, 0.0);
    lmh::Vector2f dx = lmh::Vector2f(0.0, 0.0);
    lmh::Vector2f dv = lmh::Vector2f(0.0, 0.0);


    double h = 0.01;

    this->force = (lmh::Vector2f(0.0, 0.0));
    for (int i = 0; i < attached.size(); ++i) {
        if(attached[i].gB() != this) {
            dx1 = this->gVel()*h;

            dv1 = diffeq(this->gPos(), attached[i].gB()->gPos(), this->gVel(), attached[i].gB()->gPos(), i)*h;
            //dv1 = (this->gForce())*h;

            dx2 = (this->gVel() + dv1*0.5)*h;

            dv2 = diffeq(this->gPos() + dx1*0.5, attached[i].gB()->gPos(), this->gVel() + dv1*0.5, attached[i].gB()->gPos(), i)*h;
            //dv2 = this->gForce(dx1*0.5, dv1*0.5)*h;

            dx3 = (this->gVel() + dv2*0.5)*h;
            dv3 = this->gForce(dx2*0.5, dv1*0.5)*h;

            dx4 = (this->gVel() + dv3)*h;
            dv4 = this->gForce( dx3,  dv1)*h;

            lmh::Vector2f dv = (dv1 + dv2*2.0+ dv3*2.0 + dv4)*(1.0/6.0);
            lmh::Vector2f dx = (dx1 + dx2*2.0 + dx3*2.0 + dx4)*(1.0/6.0);
            this->force+=diffeq(this->gPos()+dx, attached[i].gB()->gPos(), this->gVel()+dv, attached[i].gB()->gVel(), i);
        } else {
            this->force+=diffeq(this->gPos()+dx, attached[i].gA()->gPos(), this->gVel()+dv, attached[i].gA()->gVel(), i);

        }
    }


}


double MPoint::gMass() const {

    return this->mass;
}

void MPoint::attach_spring(Spring& s) {
    this->attached.push_back(s);
}

lmh::Vector2f MPoint::diffeq(const lmh::Vector2f& target_pos, const lmh::Vector2f& current_pos, const lmh::Vector2f& target_vel ,const lmh::Vector2f& current_vel, const int& index) const {
    //The force acting on A!
    //  a = k(lo - x)/M

    /*return lmh::Vector2f(
            ( this->gA().gPos()).normalize()*(this->spr.gl0() - lmh::Vector2f(this->gA().gPos() - this->B.gPos()).norm())*(this->spr.gK())
    );*/

    return lmh::Vector2f(
            ((target_pos-current_pos)*(this->attached[index].gl0()/(target_pos-current_pos).norm()) - (target_pos-current_pos))*this->attached[index].gK() -
                    velocity*damping + lmh::Vector2f(0, 1000)
    );

}




