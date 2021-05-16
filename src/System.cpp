//
// Created by leo on 4/28/21.
//

#include "System.h"
#include <fstream>
#include "MPoint.h"
#include "Window.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "Shader.h"
#include <SFML/Graphics.hpp>


System::System()  {
    MPoint *mp1 = new MPoint(lmh::Vector2f(0.0 + 400, 120.0 + 400), lmh::Vector2f(0.0 ,0.0), lmh::Vector2f(0.0,0.0), 10);
    MPoint *mp2 = new MPoint(lmh::Vector2f(0.0 + 400, 70 + 480), lmh::Vector2f(0.0,0.0), lmh::Vector2f(0.0,0.0), 10);
    MPoint *mp3 = new MPoint(lmh::Vector2f(103.9230484541326376116 + 400, 60.0 + 400), lmh::Vector2f(0.0,0.0), lmh::Vector2f(0.0,0.0), 10);
    MPoint* mp4 = new MPoint(lmh::Vector2f(0.0+550, 440.0), lmh::Vector2f(0.0, 0.0), lmh::Vector2f(0.0, 0.0), 10);

    Spring spr1(100.0, 3, 100.0);
    Spring spr2(100.0, 3, 100.0);
    Spring spr3 (100.0, 3, 100.0);
    Spring spr4(500.0, 3, 50.0);
    //Spring spr5(100.0, 3, 100.0);


    spr1.sA(mp1);
    spr1.sB(mp2);
    spr2.sA(mp2);
    spr2.sB(mp3);
    spr3.sA(mp3);
    spr3.sB(mp1);
    spr4.sA(mp4);
    spr4.sB(mp1);
    //spr5.sA(mp4);
    //spr5.sB(mp3);

    mp1->attach_spring(spr1);
    mp1->attach_spring(spr3);
    mp1->attach_spring(spr4);
    mp2->attach_spring(spr1);
    mp2->attach_spring(spr2);
    mp3->attach_spring(spr3);
    mp3->attach_spring(spr2);
    //mp3->attach_spring(spr5);
    mp4->attach_spring(spr4);
    //mp4->attach_spring(spr5);



    mPoints.push_back(mp1);
    mPoints.push_back(mp2);
    mPoints.push_back(mp3);
    mPoints.push_back(mp4);


    springs.push_back(spr1);
    springs.push_back(spr2);
    springs.push_back(spr3);
    springs.push_back(spr4);
    //springs.push_back(spr5);

    mp1->sDamp(0.0);
    mp2->sDamp(0.0);
    mp3->sDamp(0.0);
    mp4->sDamp(0.0);
}

/*
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
//}*/



void System::simulate(const double& max_time) {
    // set the time to zero

    std::ofstream file("../../system2.txt");


    double time = 0.0;

    int n = 0;


    std::array<lmh::Vector2f, 2> temp;
    std::vector<MPoint> temp_mpoints = {MPoint(lmh::Vector2f(0, 0), lmh::Vector2f(0, 0), lmh::Vector2f(0, 0), 0),
                                        MPoint(lmh::Vector2f(0, 0), lmh::Vector2f(0, 0), lmh::Vector2f(0, 0), 0),
                                        MPoint(lmh::Vector2f(0, 0), lmh::Vector2f(0, 0), lmh::Vector2f(0, 0), 0),
                                        //MPoint(lmh::Vector2f(0, 0), lmh::Vector2f(0, 0), lmh::Vector2f(0, 0), 0)
    };



    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML is superior!");

    std::vector<sf::CircleShape> shapes {
        sf::CircleShape(7, 6),
        sf::CircleShape(7, 6),
        sf::CircleShape(7, 6),
        //sf::CircleShape(7,6)
    };

    window.setFramerateLimit(200);

    sf::CircleShape circ(20, 12);
    circ.setPosition(0-circ.getRadius()/2.0 ,0 - circ.getRadius()/2.0);

    while (time < max_time && window.isOpen()) {

        // for loop that iterates on mPoints
        for (int i = 0; i < mPoints.size(); ++i) {

            temp = mPoints[i]->comp_next(i);

            temp_mpoints[i].sPos(temp[0]);
            temp_mpoints[i].sVel(temp[1]);

            // now update the position for the current masspoint

        }

        for (int i = 0; i < temp_mpoints.size(); ++i) {
            this->mPoints[i]->sPos(temp_mpoints[i].gPos());
            this->mPoints[i]->sVel(temp_mpoints[i].gVel());
        }



        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        for (int i = 0; i < mPoints.size(); ++i) {
            shapes[i].setPosition(mPoints[i]->gPos().gX()+400, mPoints[i]->gPos().gY()+400);
        }

        for (int i = 0; i < mPoints.size(); ++i) {
            mPoints[i]->sDrawable(10, 7);
            mPoints[i]->draw(&window);
            //springs[i].draw(&window);
        }
        file<<time<<"\t"<<this->total_kinetic()<<"\n";
        //springs[4].draw(&window);

        //window.draw(circ);

        window.display();
        window.clear();


        n++;
        time += dt;

    }

    file.close();
}

    void System::write_to_file() {
        std::ofstream file("../system.txt");
        double time = 0.0;
        for (int i = 0; i < this->data[0].size(); i++) {
            file << time << "\t" << this->data[0].at(i).gX() << "\t" << this->data[0].at(i).gY() << "\n";
            time += this->dt;
        }

        file.close();
    }

    System::~System()
    {
        for (int i = 0; i < this->mPoints.size(); ++i) {
            delete mPoints[i];
        }

    }

    double System::total_kinetic() {
    double E_cin = 0.0;
        for (int i = 0; i < mPoints.size(); ++i) {
            E_cin += (mPoints[i]->gVel()).norm()*(mPoints[i]->gVel()).norm() * 0.5;
        }
        for (int i = 0; i < springs.size(); ++i) {
            E_cin+=springs[i].gEnergy();
        }
        return E_cin;
}

void System::simulatev2(const double &max_time) {
    std::vector<std::array<lmh::Vector2f, 5>> koefsx;
    koefsx.resize(mPoints.size());

    std::vector<std::array<lmh::Vector2f, 5>> koefsv;
    koefsv.resize(mPoints.size());

    std::vector<std::array<lmh::Vector2f, 2>> initial_pos_vel;
    initial_pos_vel.resize(mPoints.size());

    for (int i = 0; i < mPoints.size(); ++i) {
        initial_pos_vel[i][0] = mPoints[i]->gPos();
        initial_pos_vel[i][1] = mPoints[i]->gVel();
    }

    std::vector<lmh::Vector2f> tempkx;
    std::vector<lmh::Vector2f> tempkv;
    double time = 0;

    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML is superior!");

    window.setFramerateLimit(140);
    std::ofstream file("../../system.txt");

    sf::CircleShape centre(20,10);
    centre.setFillColor(sf::Color::Cyan);

    while (window.isOpen()){


        for (int i = 0; i < mPoints.size(); ++i) {
            initial_pos_vel[i][0] = mPoints[i]->gPos();
            initial_pos_vel[i][1] = mPoints[i]->gVel();
        }


        for (int i = 0; i < mPoints.size(); ++i) {
            koefsx[i][0] = mPoints[i]->gVel()*dt;
            koefsv[i][0] = mPoints[i]->gForce()*dt;
            //tempkx.push_back(koefsx[i][0]);
            //tempkv.push_back(koefsv[i][0]);
        }
        for (int i = 0; i < mPoints.size(); ++i) {
            mPoints[i]->sPos(initial_pos_vel[i][0] + koefsx[i][0]*0.5);
            mPoints[i]->sVel(initial_pos_vel[i][1] + koefsv[i][0]*0.5);
        }
        for (int i = 0; i < mPoints.size(); ++i) {
            koefsx[i][1] = mPoints[i]->gVel()*dt;
            koefsv[i][1] = mPoints[i]->gForce()*dt;
            //tempkx[i] = kx2;
            //tempkv[i] = kv2;
        }
        for (int i = 0; i < mPoints.size(); ++i) {
            mPoints[i]->sPos(initial_pos_vel[i][0] + koefsx[i][1]*0.5);
            mPoints[i]->sVel(initial_pos_vel[i][1] + koefsv[i][1]*0.5);
        }

        for (int i = 0; i < mPoints.size(); ++i) {
            koefsx[i][2] = mPoints[i]->gVel()*dt;
            koefsv[i][2] = mPoints[i]->gForce()*dt;
            //tempkx[i] = kx3;
            //tempkv[i] = kv3;
        }
        for (int i = 0; i < mPoints.size(); ++i) {
            mPoints[i]->sPos(initial_pos_vel[i][0] + koefsx[i][2]);
            mPoints[i]->sVel(initial_pos_vel[i][1] + koefsv[i][2]);
        }

        for (int i = 0; i < mPoints.size(); ++i) {
            koefsx[i][3] = mPoints[i]->gVel()*dt;
            koefsv[i][3] = mPoints[i]->gForce()*dt;
            //tempkx[i] = kx4;
            //tempkv[i] = kv;
        }
        for (int i = 0; i < mPoints.size(); ++i) {
            mPoints[i]->sPos(initial_pos_vel[i][0] + koefsx[i][3]);
            mPoints[i]->sVel(initial_pos_vel[i][1] + koefsv[i][3]);
        }

        for (int i = 0; i < mPoints.size(); ++i) {
            koefsx[i][4] = (koefsx[i][0] + koefsx[i][1]*2.0 + koefsx[i][2]*2.0 + koefsx[i][3])*(1.0/6.0);
            koefsv[i][4] = (koefsv[i][0] + koefsv[i][1]*2.0 + koefsv[i][2]*2.0 + koefsv[i][3])*(1.0/6.0);
        }
        for (int i = 0; i < mPoints.size(); ++i) {

            mPoints[i]->sPos(initial_pos_vel[i][0] + koefsx[i][4]);
            mPoints[i]->sVel(initial_pos_vel[i][1] + koefsv[i][4]);

        }


        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        for (int i = 0; i < mPoints.size(); ++i) {
            mPoints[i]->sDrawable(10, 7);
            mPoints[i]->draw(&window);
            //springs[i].draw(&window);
        }

        centre.setPosition(this->geom_centre().gX(), this->geom_centre().gY());
        std::cout<<geom_centre();
        window.draw(centre);


        window.display();
        window.clear();
        file<<time<<"\t"<<this->total_kinetic()<<"\n";

        time+=dt;

    }

}

lmh::Vector2f System::geom_centre() {
    lmh::Vector2f to_ret(0.0, 0.0);
    for (int i = 0; i < mPoints.size(); ++i) {
        to_ret = to_ret + mPoints[i]->gPos();
        //std::cout<<mPoints[i]->gPos();
    }
    return to_ret*(1.0/(mPoints.size()));
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

