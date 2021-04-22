#include <iostream>
#include "Vector2f.h"
#include "Spring.h"
#include "Vector3f.h"
#include <vector>
#include <fstream>

void simulate();

int main() {
    lmh::Vector2f vector(3, 5);
    lmh::Vector2f vector2(1,1);

    simulate();

    return 0;
}

void simulate(){
    Spring spring(100, 0, 15);
    MPoint stationary(lmh::Vector2f(0, 0), lmh::Vector2f(0, 0), lmh::Vector2f(0, 0), 50);
    MPoint attached(lmh::Vector2f(0, 12), lmh::Vector2f(0, 0), lmh::Vector2f(0, 0), 5);

    double t = 0;
    double dt = 0.005;
    double t_end = 10.0;

    spring.sA(attached);
    spring.sB(stationary);

    std::vector<lmh::Vector2f> pos;
    std::vector<lmh::Vector2f> vel;
    std::vector<lmh::Vector2f> force;
    //set initial condition

    pos.push_back(attached.gPos());
    vel.push_back(attached.gVel());

    // v_n+1 = v_n + (F)/m * dt

    //pos.push_back(attached.)

    lmh::Vector2f temp;
    int iter = 0;

    while(t<t_end){
        temp = spring.compute_force();
        force.push_back(temp);

        attached.sForce(temp);
        //compute the velocity at the next frame
        vel.push_back( vel[iter] + (attached.gForce())*(1/attached.gMass())*dt );

        //compute the position
        pos.push_back( pos[iter] + vel[iter]*dt);

        //
        attached.sPos(pos[++iter]);
        spring.sA(attached);


        t+=dt;
    }

    std::ofstream file("C:\\Users\\emils\\Desktop\\pos.txt");



    for(int x = 0; x<pos.size(); x++){
        std::cout<< "position : " << pos[x];
        std::cout <<"velocity"<< vel[x];
        std::cout <<"force"<< force[x] << std::endl;
        file<<pos[x].gY()<<"\n";

    }
};