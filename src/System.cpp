#include "System.h"
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

    mp1->sDamp(1.7);
    mp2->sDamp(1.8);
    mp3->sDamp(1.9);
    mp4->sDamp(0.99);

    //INITIALOZE OBSTACLES
    for (int i = 0; i <mPoints.size() ; ++i) {
        mPoints[i]->sR(20.0);
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
    sf::RenderWindow window(sf::VideoMode((int)WIDTH, (int)HEIGHT), "SFML is superior!");

    window.setFramerateLimit(30);



    //initialize the walls
    double offset = 20.0;
    Walls walls(window);

    Obstacle ob1(offset, window.getSize().y/2.0, window.getSize().x/4.0, window.getSize().y - window.getSize().y/1.5 - offset , &window);
    Obstacle ob2(window.getSize().x-offset, window.getSize().y/2.0, (-1)*(window.getSize().x/4.0), window.getSize().y - window.getSize().y/1.5 - offset , &window);
    obstacles.push_back(ob1);
    obstacles.push_back(ob2);


    while (window.isOpen()){

        compute_RK4(koefsx, koefsv, initial_pos_vel);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        for (int i = 0; i < mPoints.size(); ++i) {
            mPoints[i]->sDrawable();
            mPoints[i]->draw(&window);
        }

        for (int i = 0; i < springs.size(); ++i) {
            springs[i].draw(&window);
        }

        for (int i = 0; i < obstacles.size(); ++i) {
            obstacles[i].draw(window);
        }


        walls.draw_walls(offset);
        collision(walls);
        collision();


        window.display();
        window.clear();
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
        if (currentPosition.gX()-mPoints[i]->gR()< walls.gXl() ) {
            mPoints[i]->sVel(lmh::Vector2f(-mPoints[i]->gVel().gX(), mPoints[i]->gVel().gY()));
            //correct the position
            mPoints[i]->sPos({walls.gXl()+mPoints[i]->gR(), mPoints[i]->gPos().gY()});
        }
        if(currentPosition.gX()+mPoints[i]->gR()>walls.gXr()) {
            mPoints[i]->sVel(lmh::Vector2f(-mPoints[i]->gVel().gX(), mPoints[i]->gVel().gY()));
            //correct the position
            mPoints[i]->sPos({walls.gXr()-mPoints[i]->gR(), mPoints[i]->gPos().gY()});


        }
        if (currentPosition.gY()-mPoints[i]->gR()< walls.gYu()){
            mPoints[i]->sVel(lmh::Vector2f(mPoints[i]->gVel().gX(), -mPoints[i]->gVel().gY()));
            mPoints[i]->sPos({mPoints[i]->gPos().gX(), walls.gYu()+mPoints[i]->gR()});

        }
        if (currentPosition.gY()+mPoints[i]->gR()>walls.gYd()) {
            mPoints[i]->sVel(lmh::Vector2f(mPoints[i]->gVel().gX(), -mPoints[i]->gVel().gY()));
            mPoints[i]->sPos({mPoints[i]->gPos().gX(), walls.gYd()-mPoints[i]->gR()});

        }
    }
}

void System::collision(){


    /*
    *** FIRST CHECK COLLISIONS BETWEEN THE BALLS :
     */

    /*
     *
     * SORT the mPoints
     * Consider to write a function insertion_sort() instead of using qsort of the STL
     * because the array is will be partially sorted
     *
     */

    std::sort(mPoints.begin(), mPoints.end(),[](MPoint* a, MPoint* b){
        return a->gPos().gX()  < b->gPos().gX();
    });

    for (int i = 0; i < mPoints.size(); ++i) {
        for (int j = i+1 ; (j < mPoints.size()) && ((mPoints[i]->gPos().gX() + mPoints[i]->gR()) > (mPoints[j]->gPos().gX() - mPoints[j]->gR())) ; ++j) {
            //solve collisions between the two
            collision(i, j);
        }
    }

    /*
     * AFTER CHECK THE COLLISION BETWEEN THE BALLS AND THE OBSTACLES
     */

    for (int i = 0; i < mPoints.size(); ++i) { //iterating over balls
        for (int j = 0; j < obstacles.size(); ++j) { //iterating over obstacles

            if (does_collide(i, j)){
                //RESOLVE COLLISION BY UPDATING THE VELOCITIES

                collision(i, &obstacles[j]);


            }

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

bool System::does_collide(const int &i, const int &j) {
    //in order to collide the center of the mPoint must be at least in the distance of
    //R of the line generated by the obstacle

    if (mPoints[i]->get_distance(obstacles[j]) <= mPoints[i]->gR()){

        lmh::Vector2f diff = mPoints[i]->gPos() - obstacles[j].origin;
        lmh::Vector2f vec_unit = obstacles[j].vector.normalize(obstacles[j].vector);
        double vec_lenght = obstacles[j].vector.norm();


        bool left = ((diff).dot(vec_unit) <= -mPoints[i]->gR());
        bool right = ( (diff).dot(vec_unit) >=
                     mPoints[i]->gR() + vec_lenght);

        if (left || right)
        {
            return false;
        } else{
            return true;
        }

    } else{
        return false;
    }
}

void System::collision(const int &i, Obstacle *p_obst) {
    //first take the dot product of the velocity w/ the Obstacle::vector
    //to get the Y component in the new coordinate system

    lmh::Vector2f colinear(-(p_obst->vector.gX()), -(p_obst->vector.gY()));
    lmh::Vector2f normal(p_obst->vector.gY() , -(p_obst->vector.gX()));


    lmh::Vector2f unit_col = colinear.normalize();
    lmh::Vector2f unit_normal = normal.normalize();


    lmh::Vector2f v_conserved = unit_col*(unit_col.dot(mPoints[i]->gVel()));
    lmh::Vector2f v_opposite = unit_normal*(-1)*(unit_normal.dot(mPoints[i]->gVel()));

    mPoints[i]->sVel(v_conserved+v_opposite);

    //rectify the position

    lmh::Vector2f vec(p_obst->vector);
    lmh::Vector2f dir = vec.normalize();

    lmh::Vector2f to_center = mPoints[i]->gPos() - p_obst->origin;
    lmh::Vector2f perp = to_center - dir*to_center.dot(dir);

    float pendepth = mPoints[i]->gR() - perp.norm();

    mPoints[i]->sPos(mPoints[i]->gPos()+perp.normalize()*pendepth);


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

void System::config_1() {
    lmh::Vector2f start_point(100.0, 3*offset);


    this->mPoints.resize(54);
    int id = 0;
    for (int i = 0; i < 6; ++i) {
        for (int j = 0; j < 9; ++j) {
            mPoints[id] = new MPoint(lmh::Vector2f(start_point.gX() + 35*j, start_point.gY() + 30*i), lmh::Vector2f(0.0, 0.0), lmh::Vector2f(0.0, 0.0), 10, 0.1);
            mPoints[id]->sR(8);
        id++;
        }

    }

    //this->springs.resize(48+54);


    for (int i = 0; i < 48+45; ++i) {
        if (i<48){
            springs.emplace_back(500.0, 10, 35);

        } else{
            //springs.emplace_back(500.0, 10, 30);
        }

    }

    id=0;

    for(int j = 0; j<=7; ++j){
        springs[j].sA(mPoints[j]);
        springs[j].sB(mPoints[j+1]);
    }

    for(int j = 8; j<=15; ++j){
        springs[j].sA(mPoints[j+1]);
        springs[j].sB(mPoints[j+2]);
    }

    for(int j = 18; j<=23; ++j){
        springs[j].sA(mPoints[j+2]);
        springs[j].sB(mPoints[j+3]);
    }
    for(int j = 24; j<=31; ++j){
        springs[j].sA(mPoints[j+3]);
        springs[j].sB(mPoints[j+4]);
    }
    for(int j = 32; j<=39; ++j){
        springs[j].sA(mPoints[j+4]);
        springs[j].sB(mPoints[j+5]);
    }
    for(int j = 40; j<=47; ++j){
        springs[j].sA(mPoints[j+5]);
        springs[j].sB(mPoints[j+6]);
    }



    mPoints[0]->attach_spring(springs[0]);
    for(int j = 1; j<8; ++j){
        mPoints[j]->attach_spring(springs[j-1]);
        mPoints[j]->attach_spring(springs[j]);
    }
    mPoints[8]->attach_spring(springs[7]);

    mPoints[9]->attach_spring(springs[8]);
    for(int j = 10; j<17; ++j){
        mPoints[j]->attach_spring(springs[j-2]);
        mPoints[j]->attach_spring(springs[j-1]);
    }
    mPoints[17]->attach_spring(springs[15]);

    mPoints[18]->attach_spring(springs[16]);
    for(int j = 19; j<26; ++j){
        mPoints[j]->attach_spring(springs[j-2]);
        mPoints[j]->attach_spring(springs[j-3]);
    }
    mPoints[26]->attach_spring(springs[23]);

    mPoints[27]->attach_spring(springs[24]);
    for(int j = 28; j<35; ++j){
        mPoints[j]->attach_spring(springs[j-3]);
        mPoints[j]->attach_spring(springs[j-4]);
    }
    mPoints[35]->attach_spring(springs[31]);

    mPoints[36]->attach_spring(springs[32]);
    for(int j = 37; j<44; ++j){
        mPoints[j]->attach_spring(springs[j-4]);
        mPoints[j]->attach_spring(springs[j-5]);
    }
    mPoints[44]->attach_spring(springs[39]);

    mPoints[45]->attach_spring(springs[40]);
    for(int j = 46; j<53; ++j){
        mPoints[j]->attach_spring(springs[j-6]);
        mPoints[j]->attach_spring(springs[j-7]);
    }
    mPoints[53]->attach_spring(springs[46]);



}
