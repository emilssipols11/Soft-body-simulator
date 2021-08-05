#include "System.h"
#include "MPoint.h"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <cmath>
#include <sstream>
#include "Spring.h"


//initialize the system
System::System()  {

    //The constructor initializes the system using the config1() method
    config_1();


}

    double System::total_kinetic() {
    double E_cin = 0.0;
        for (int i = 0; i < mPoints.size(); ++i) {
            E_cin += (mPoints[i]->gVel()).norm()*(mPoints[i]->gVel()).norm() * 0.5;
        }
        for (int i = 0; i < springs.size(); ++i) {
            E_cin+=springs[i]->gEnergy();
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

    //initialize the window and related things such as the text
    sf::RenderWindow window(sf::VideoMode((int)WIDTH, (int)HEIGHT), "SFML is superior!");

    window.setFramerateLimit(120);

    sf::Text*text = new sf::Text[2];
    sf::Font font;
    if (!font.loadFromFile("../../arial.ttf"))
    {
        std::cerr<<"ERROR LOADING FONT\n";
    }
    text[0].setFont(font);
    text[1].setFont(font);


    //initialize the walls
    double offset = 20.0;
    Walls walls(window);



    while (window.isOpen()){

        compute_RK4(koefsx, koefsv, initial_pos_vel);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                window.close();
            }
            if(event.type == sf::Event::KeyPressed){
                if (event.key.code == sf::Keyboard::Up){
                    MPoint::GRAVITY+=5;
                }
                if (event.key.code == sf::Keyboard::Down){
                    MPoint::GRAVITY-=5;
                }
            }

        }

        for (int i = 0; i < mPoints.size(); ++i) {
            mPoints[i]->sDrawable();
            mPoints[i]->draw(&window);
        }

        for (int i = 0; i < springs.size(); ++i) {
            springs[i]->draw(&window);
        }

        for (int i = 0; i < obstacles.size(); ++i) {
            obstacles[i]->draw(window);
        }

        draw_text(time, text, window);

        walls.draw_walls(offset);
        collision(walls);
        collision();



        window.display();
        window.clear();
        time+=dt;

    }

    delete[] text;

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
    for (int i = 0; i < this->springs.size(); ++i) {
        delete springs[i];
    }
    for (int i = 0; i < this->obstacles.size() ;++i) {
        delete obstacles[i];
    }

}

void System::collision(Walls &walls) {
    lmh::Vector2f currentPosition;
    for (int i = 0; i < mPoints.size(); ++i) {
        currentPosition = mPoints[i]->gPos();
        if (currentPosition.gX()-mPoints[i]->gR()< walls.gXl() ) {
            mPoints[i]->sVel(lmh::Vector2f((-mPoints[i]->gVel().gX())*mPoints[i]->get_elasticity(), mPoints[i]->gVel().gY()));
            //correct the position
            mPoints[i]->sPos({walls.gXl()+mPoints[i]->gR(), mPoints[i]->gPos().gY()});
        }
        if(currentPosition.gX()+mPoints[i]->gR()>walls.gXr()) {
            mPoints[i]->sVel(lmh::Vector2f((-mPoints[i]->gVel().gX())*mPoints[i]->get_elasticity(), mPoints[i]->gVel().gY()));
            //correct the position
            mPoints[i]->sPos({walls.gXr()-mPoints[i]->gR(), mPoints[i]->gPos().gY()});


        }
        if (currentPosition.gY()-mPoints[i]->gR()< walls.gYu()){
            mPoints[i]->sVel(lmh::Vector2f(mPoints[i]->gVel().gX(), (-mPoints[i]->gVel().gY()))*mPoints[i]->get_elasticity());
            mPoints[i]->sPos({mPoints[i]->gPos().gX(), walls.gYu()+mPoints[i]->gR()});

        }
        if (currentPosition.gY()+mPoints[i]->gR()>walls.gYd()) {
            mPoints[i]->sVel(lmh::Vector2f(mPoints[i]->gVel().gX(), (-mPoints[i]->gVel().gY())*mPoints[i]->get_elasticity()));
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

                collision(i, obstacles[j]);


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

    if (mPoints[i]->get_distance(*obstacles[j]) <= mPoints[i]->gR()){

        lmh::Vector2f diff = mPoints[i]->gPos() - obstacles[j]->origin;
        lmh::Vector2f vec_unit = obstacles[j]->vector.normalize(obstacles[j]->vector);
        double vec_lenght = obstacles[j]->vector.norm();


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

    mPoints[i]->sVel((v_conserved+v_opposite)*mPoints[i]->get_elasticity());

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


    /****
     ****
     * INITIAL CONFIGURATION FOR THE BODY AND OBSTACLES
     ****
     ****
     *****/


    int num_of_balls_horizontal = 12;
    int num_of_balls_vertical = 8;
    double increment_horizontal = 40;
    double increment_vertical = 40;
    double starting_point_x = WIDTH/2 - (num_of_balls_horizontal/2)*increment_horizontal;
    double starting_point_y = 2*offset;
    double elasticity = 0.9;
    lmh::Vector2f nul(0.0, 0.0);
    for(int j=0; j<num_of_balls_vertical; ++j) {
        for (int i = 0; i < num_of_balls_horizontal; ++i) {
            mPoints.push_back(new MPoint(
                    lmh::Vector2f(starting_point_x + i * increment_horizontal*1.5, starting_point_y + j * increment_vertical*1.5),
                    nul, nul, 10, 0.2));
        }
    }

    //springs for all near mPoints
    for (int i = 0; i < (num_of_balls_horizontal-1)*num_of_balls_vertical; ++i) {
        springs.push_back(new Spring(100, 0.0, increment_horizontal*1.5));
    }


    //now attach all horizontal springs
    int diff_offset = 0;
    for (int i = 0; i < num_of_balls_vertical; ++i) {
        for (int j = 0; j < (num_of_balls_horizontal-1); ++j) {
            springs[j+num_of_balls_horizontal*i-diff_offset]->sA(mPoints[j+num_of_balls_horizontal*i]);
            springs[j+num_of_balls_horizontal*i-diff_offset]->sB(mPoints[j+num_of_balls_horizontal*i + 1]);
        }
        diff_offset++;
    }
    diff_offset = 0;
    for (int i = 0; i < num_of_balls_vertical; ++i) {
        for (int j = 0; j < (num_of_balls_horizontal-1); ++j) {
            mPoints[j+num_of_balls_horizontal*i]->attach_spring(*springs[j+num_of_balls_horizontal*i-diff_offset]);
            mPoints[j+num_of_balls_horizontal*i + 1]->attach_spring(*springs[j+num_of_balls_horizontal*i-diff_offset]);
        }
        diff_offset++;
    }


    for (int i = 0; i < mPoints.size(); ++i) {
        mPoints[i]->sR(10);
    }

    //create vertical spring connections
    int temp_size_horozintal = springs.size();

    for (int i = 0; i < num_of_balls_horizontal*(num_of_balls_vertical-1); ++i) {
        springs.push_back(new Spring(1000, 0.0, increment_vertical*1.5));
    }

    diff_offset = 0;


    for (int i = 0; i < num_of_balls_horizontal; ++i) {
        for (int j = 0; j < (num_of_balls_vertical-1); ++j) {
            springs[temp_size_horozintal+i*num_of_balls_vertical + j - diff_offset]->sA(mPoints[i + j*num_of_balls_horizontal ]);
            springs[temp_size_horozintal+i*num_of_balls_vertical + j - diff_offset]->sB(mPoints[i + j*num_of_balls_horizontal + num_of_balls_horizontal]);

        }
        diff_offset++;
    }

    diff_offset = 0;

    for (int i = 0; i < num_of_balls_horizontal; ++i) {
        for (int j = 0; j < (num_of_balls_vertical-1); ++j) {
            mPoints[i + j*num_of_balls_horizontal]->attach_spring(*springs[temp_size_horozintal+i*num_of_balls_vertical+j-diff_offset]);
            mPoints[i + j*num_of_balls_horizontal + num_of_balls_horizontal]->attach_spring(*springs[temp_size_horozintal+i*num_of_balls_vertical+j-diff_offset]);
        }
        diff_offset++;
    }

    //create diagonal connections

    temp_size_horozintal = springs.size();

    //create extra springs of the same size
    double square_root2 = sqrt(2);
    for (int i = 0; i < (num_of_balls_horizontal-1)*(num_of_balls_vertical-1); ++i) {
        springs.push_back(new Spring(10000, 0.0, increment_horizontal*1.5*square_root2));
    }

    diff_offset = 0;

    for (int i = 0; i < (num_of_balls_vertical-1) ; ++i) {
        for (int j = 0; j <(num_of_balls_horizontal-1) ; ++j) {
            springs[temp_size_horozintal + j+i*num_of_balls_horizontal - diff_offset]->sA(mPoints[j+i*num_of_balls_horizontal]);
            springs[temp_size_horozintal + j+i*num_of_balls_horizontal - diff_offset]->sB(mPoints[j+1+(i+1)*num_of_balls_horizontal]);

        }
        diff_offset+=1;

    }

    diff_offset = 0;

    for (int i = 0; i < (num_of_balls_vertical-1) ; ++i) {
        for (int j = 0; j <(num_of_balls_horizontal-1) ; ++j) {

            mPoints[j+i*num_of_balls_horizontal]->attach_spring(*springs[temp_size_horozintal + j+i*num_of_balls_horizontal - diff_offset]);
            mPoints[j+1+(i+1)*num_of_balls_horizontal]->attach_spring(*springs[temp_size_horozintal + j+i*num_of_balls_horizontal - diff_offset]);

        }
        diff_offset+=1;

    }


    temp_size_horozintal = springs.size();

    for (int i = 0; i < (num_of_balls_horizontal-1)*(num_of_balls_vertical-1); ++i) {
        springs.push_back(new Spring(10000, 0.0, increment_horizontal*1.5*square_root2));
    }

    diff_offset = 0;

    for (int i = 0; i < (num_of_balls_vertical-1) ; ++i) {
        for (int j = 0; j <(num_of_balls_horizontal-1) ; ++j) {
            springs[temp_size_horozintal + j+i*num_of_balls_horizontal - diff_offset]->sA(mPoints[j+1+i*num_of_balls_horizontal]);
            springs[temp_size_horozintal + j+i*num_of_balls_horizontal - diff_offset]->sB(mPoints[j+(i+1)*num_of_balls_horizontal]);

        }
        diff_offset+=1;

    }

    diff_offset = 0;

    for (int i = 0; i < (num_of_balls_vertical-1) ; ++i) {
        for (int j = 0; j <(num_of_balls_horizontal-1) ; ++j) {

            mPoints[j+1+i*num_of_balls_horizontal]->attach_spring(*springs[temp_size_horozintal + j+i*num_of_balls_horizontal - diff_offset]);
            mPoints[j+(i+1)*num_of_balls_horizontal]->attach_spring(*springs[temp_size_horozintal + j+i*num_of_balls_horizontal - diff_offset]);

        }
        diff_offset+=1;

    }

    //set the elasticity
    for (int i = 0; i < mPoints.size(); ++i) {
        mPoints[i]->sElasticity(0.7);
    }

    for (int i = 0; i < mPoints.size(); ++i) {
        mPoints[i]->sDamp(0.5);
    }

    Obstacle* ob1 = new Obstacle(offset, HEIGHT/2.0, WIDTH - offset, HEIGHT/2.0 - offset*5  );
    obstacles.push_back(ob1);
    MPoint::GRAVITY = 150;




 }

void System::draw_text(const double &time, sf::Text *text ,sf::RenderWindow &w) {
    std::stringstream type;
    type<<time;
    text[0].setString(type.str());
    text[0].setCharacterSize(24);
    text[0].setPosition(2*offset, 2*offset);
    text[0].setFillColor(sf::Color::Yellow);
    text[0].setStyle(sf::Text::Bold);

    std::stringstream type2;
    type2<<MPoint::GRAVITY;
    text[1].setString("GRAVITY: " + type2.str() + " units\n\n\n" + "To change the gravity press\nthe Up or Down keys...");
    text[1].setCharacterSize(24);
    text[1].setPosition(2*offset, 150);
    text[1].setFillColor(sf::Color::Yellow);
    text[1].setStyle(sf::Text::Bold);




    w.draw(text[1]);
    w.draw(text[0]);


}

