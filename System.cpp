//
// Created by leo on 4/28/21.
//

#include "System.h"
#include <fstream>
#include "MPoint.h"


System::System()  {
    MPoint *mp1 = new MPoint(lmh::Vector2f(0.0, 12.0), lmh::Vector2f(0.0,0.0), lmh::Vector2f(0.0,0.0), 10);
    MPoint *mp2 = new MPoint(lmh::Vector2f(0.0, 0.0), lmh::Vector2f(0.0,0.0), lmh::Vector2f(0.0,0.0), 10);

    Spring spr(100.0, 3, 10.0);

    spr.sA(mp1);
    spr.sB(mp2);

    mp1->attach_spring(spr);
    mp2->attach_spring(spr);

    mPoints.push_back(mp1);
    mPoints.push_back(mp2);
}

//the argument must be the mpoint
//std::array<lmh::Vector2f, 2> System::comp_next(const int& i) {
//
//    lmh::Vector2f dx1, dx2, dx3, dx4, dv1, dv2, dv3, dv4;
//    double h = 0.01;
//
//
//    //DX1 = mPoints[i].gForce
//
//    dx1 = this->mPoints[i]->gPos()*h;
//
//    //dv1 = mpoint.getForce()*(1/M)
//    dv1 = (this->mPoints[i]->gForce())(prev_pos, prev_vel)*h;
//
//    dx2 = (prev_vel + dv1*0.5)*h;
//    dv2 = (this->dip.diffeq)(prev_pos + dx1*0.5, prev_vel + dv1*0.5)*h;
//
//    dx3 = (prev_vel + dv2*0.5)*h;
//    dv3 = (this->dip.diffeq)(prev_pos + dx2*0.5, prev_vel + dv1*0.5)*h;
//
//    dx4 = (prev_vel + dv3)*h;
//    dv4 = (this->dip.diffeq)(prev_pos + dx3, prev_vel + dv1)*h;
//
//    lmh::Vector2f dv = (dv1 + dv2*2.0+ dv3*2.0 + dv4)*(1.0/6.0);
//    lmh::Vector2f dx = (dx1 + dx2*2.0 + dx3*2.0 + dx4)*(1.0/6.0);
//
//
//    return std::array<lmh::Vector2f, 2> { prev_pos + dx , prev_vel + dv};
//}



void System::simulate(const double& max_time) {
    // set the time to zero

    std::ofstream file("../kagribi.txt");

    double time = 0.0;

    // set the initial condition (the position of the Mpoints of the dipole)
    // this->data.at(0).push_back(dip.gA().gPos());
    // this->data.at(1).push_back(dip.gA().gVel());


    int n = 0;


    std::array<lmh::Vector2f, 2> temp;
    std::vector<MPoint> temp_mpoints = {MPoint(lmh::Vector2f(0,0), lmh::Vector2f(0,0), lmh::Vector2f(0,0), 0),
                                        MPoint(lmh::Vector2f(0,0), lmh::Vector2f(0,0), lmh::Vector2f(0,0), 0)};
    //temp_mpoints.resize(mPoints.size());

    while (time<max_time){


        // for loop that iterates on MPoints


        for (int i = 0; i < mPoints.size(); ++i) {

            temp = mPoints[i]->comp_next(i);

            temp_mpoints[i].sPos(temp[0]);
            temp_mpoints[i].sVel(temp[1]);

            // now update the position for the current masspoint
            //mPoints[i]->sPos(temp[0]);
            //mPoints[i]->sVel(temp[1]);

        }

        for (int i = 0; i < temp_mpoints.size(); ++i) {
            this->mPoints[i]->sPos(temp_mpoints[i].gPos());
            this->mPoints[i]->sVel(temp_mpoints[i].gVel());
        }

        file<<time;
        // write to file
        for (int i = 0; i < this->mPoints.size(); ++i) {
            file<<"\t"<<this->mPoints[i]->gPos().gY()<<"\t";
        }
        file<<"\n";

        /*//evaluate the expression after dt
        temp = this->comp_next(this->data.at(0)[n], this->data.at(1)[n]);

        //update the position of the masspoint
        this->dip.sA(MPoint(temp[0], temp[1], lmh::Vector2f(0.0, 0.0), dip.gA().gMass()));

        //store the data in the std::vector
        this->data[0].push_back(temp[0]);
        this->data[1].push_back(temp[1]);


*/
        n++;
        time+=dt;
    }


}

void System::write_to_file() {
    std::ofstream file("../system.txt");
    double time = 0.0;
    for(int i =0; i<this->data[0].size(); i++){
        file<<time<<"\t"<<this->data[0].at(i).gX() <<"\t"<<this->data[0].at(i).gY()<<"\n";
        time+=this->dt;
    }

    file.close();
}

/*std::array<lmh::Vector2f, 2> System::simulate_euler(const double &max) {
    lmh::Vector2f dv;
    lmh::Vector2f dx;

    double time = 0;

    this->data.at(0).push_back(this->dip.gA().gPos());
    this->data.at(1).push_back(this->dip.gA().gVel());

    int n = 0;

    while (time < max){
        //compute velocity
        dv = dip.diffeq(data.at(0)[n], data.at(1)[n])*(this->dt);
        this->data.at(1).push_back(dv + this->data.at(1)[n]);

        dx = this->data.at(1)[n]*(this->dt);
        this->data.at(0).push_back(dx + this->data.at(0)[n]);

        this->dip.sA(MPoint(this->data.at(0)[n+1], this->data.at(1)[n+1], lmh::Vector2f(0.0, 0.0), dip.gA().gMass()));

        time+=dt;
        n++;
        //compute position
    }

    std::ofstream file("../rk4.txt");

    double time2 = 0;

    for (int i = 0; i < this->data.at(0).size(); ++i) {
        file<<time2<<"\t"<<this->data.at(0)[i].gY()<<"\n";
        time2+=dt;
    }


}
*/

