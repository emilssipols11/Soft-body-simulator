#include "System.h"
#include <fstream>
#include "MPoint.h"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cmath>

//initialize the system
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

    //BEGINNING OF THE INITIALIZATION
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

    double time = 0;

    //END OF INITIALIZATION

    //initialize the window
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML is superior!");

    window.setFramerateLimit(30);
    std::ofstream file("../../system.txt");

    sf::CircleShape centre(20,10);
    centre.setFillColor(sf::Color::Cyan);


    //initialize the walls
    double offset = 20.0;
    Walls walls(window);

    while (window.isOpen()){

        compute_RK4(koefsx, koefsv, initial_pos_vel);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        for (int i = 0; i < mPoints.size(); ++i) {
            mPoints[i]->sDrawable(10, 7);
            mPoints[i]->draw(&window);
            springs[i].draw(&window);
        }

        collision(walls);

        walls.draw_walls(offset);

        centre.setPosition(this->geom_centre().gX(), this->geom_centre().gY());

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
    }
    return to_ret*(1.0/(mPoints.size()));
}

void System::compute_RK4(std::vector<std::array<lmh::Vector2f, 5>> &koefsx, std::vector<std::array<lmh::Vector2f, 5>> &koefsv,
                         std::vector<std::array<lmh::Vector2f, 2>> &initial_pos_vel) {
    for (int i = 0; i < mPoints.size(); ++i) {
        initial_pos_vel[i][0] = mPoints[i]->gPos();
        initial_pos_vel[i][1] = mPoints[i]->gVel();
    }
    for (int i = 0; i < mPoints.size(); ++i) {
        koefsx[i][0] = mPoints[i]->gVel()*dt;
        koefsv[i][0] = mPoints[i]->gForce()*dt;
    }
    for (int i = 0; i < mPoints.size(); ++i) {
        mPoints[i]->sPos(initial_pos_vel[i][0] + koefsx[i][0]*0.5);
        mPoints[i]->sVel(initial_pos_vel[i][1] + koefsv[i][0]*0.5);
    }
    for (int i = 0; i < mPoints.size(); ++i) {
        koefsx[i][1] = mPoints[i]->gVel()*dt;
        koefsv[i][1] = mPoints[i]->gForce()*dt;
    }
    for (int i = 0; i < mPoints.size(); ++i) {
        mPoints[i]->sPos(initial_pos_vel[i][0] + koefsx[i][1]*0.5);
        mPoints[i]->sVel(initial_pos_vel[i][1] + koefsv[i][1]*0.5);
    }
    for (int i = 0; i < mPoints.size(); ++i) {
        koefsx[i][2] = mPoints[i]->gVel()*dt;
        koefsv[i][2] = mPoints[i]->gForce()*dt;
    }
    for (int i = 0; i < mPoints.size(); ++i) {
        mPoints[i]->sPos(initial_pos_vel[i][0] + koefsx[i][2]);
        mPoints[i]->sVel(initial_pos_vel[i][1] + koefsv[i][2]);
    }
    for (int i = 0; i < mPoints.size(); ++i) {
        koefsx[i][3] = mPoints[i]->gVel()*dt;
        koefsv[i][3] = mPoints[i]->gForce()*dt;
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
}

System::~System()
{
    for (int i = 0; i < this->mPoints.size(); ++i) {
        delete mPoints[i];
    }

}

void System::collision(Walls &walls) {
    lmh::Vector2f currentPosition;
    for (int i = 0; i < mPoints.size(); ++i) {
        currentPosition = mPoints[i]->gPos();
        if (currentPosition.gX()-mPoints[i]->gR()< walls.gXl() || currentPosition.gX()+mPoints[i]->gR()>walls.gXr()) {
            mPoints[i]->sVel(lmh::Vector2f(-mPoints[i]->gVel().gX(), mPoints[i]->gVel().gY()));
        }
        if (currentPosition.gY()-mPoints[i]->gR()< walls.gYu() || currentPosition.gY()+mPoints[i]->gR()>walls.gYd()) {
            mPoints[i]->sVel(lmh::Vector2f(mPoints[i]->gVel().gX(), -mPoints[i]->gVel().gY()));
        }
    }
}

void System::collision(){
    /*
     *
     * SORT the mPoints
     * Consider to write a function insertion_sort() instead of using qsort of the STL
     * because the array is will be partially sorted
     *
     */

    std::sort(mPoints.begin(), mPoints.end(),[](MPoint* a, MPoint* b){
        return a->gPos().gX() < b->gPos().gY();
    });

    for (int i = 0; i < mPoints.size(); ++i) {
        for (int j = i+1 ; (j < mPoints.size()) && ((mPoints[i]->gPos().gX() + mPoints[i]->gR()) > (mPoints[j]->gPos().gX() - mPoints[j]->gR())) ; ++j) {
            //solve collisions between the two
            //Collision(MPoints[i], Mpoints[j]);
        }
    }


}

void System::collision(int const& a, int const& b){
    float xik = mPoints[a]->gPos().gX() - mPoints[b]->gPos().gX();
    float yik = mPoints[a]->gPos().gY() - mPoints[b]->gPos().gY();
    float rik = sqrt(xik*xik + yik*yik);

    //check if they really collide
    if (rik < (mPoints[a]->gR() + mPoints[b]->gR())){
        //now update the parameters
        float xiku = xik / rik;
        float yiku = yik / rik;

        //change in velocity
        float dv = xiku * (mPoints[a]->gVel().gX() - mPoints[b]->gVel().gX()) +
                yiku * (mPoints[a]->gVel().gY() - mPoints[b]->gVel().gY() );

        //update the velocity
        mPoints[b]->sVel({mPoints[b]->gVel().gX() + xiku*dv,
                          mPoints[b]->gVel().gY() + yiku*dv});
        mPoints[a]->sVel({mPoints[a]->gVel().gX() - xiku*dv,
                          mPoints[a]->gVel().gY() - yiku*dv});
        //CHECK IF ONE MUST UPDATE THE POSITION
        //USING POS+=VEL
        //(THIS TASK SHOULD NORMALLY BE DONE BY THE RK4 METHOD)

        //update the position so that two mPoints
        //do not stay in collision for 2 consecutive frames
        mPoints[a]->sPos({mPoints[a]->gPos().gX() + (mPoints[a]->gR()+mPoints[b]->gR()-rik)*xiku,mPoints[a]->gPos().gY() + (mPoints[a]->gR()+mPoints[b]->gR()-rik)*yiku});
        mPoints[b]->sPos({mPoints[b]->gPos().gX() - (mPoints[a]->gR()+mPoints[b]->gR()-rik)*xiku,mPoints[b]->gPos().gY() - (mPoints[a]->gR()+mPoints[b]->gR()-rik)*yiku});

    }

}