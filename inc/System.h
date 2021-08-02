//
// Created by leo on 4/28/21.
//

#ifndef SOFT_BODY_SIMULATOR_SYSTEM_H
#define SOFT_BODY_SIMULATOR_SYSTEM_H
#include "Dipole.h"
#include "Walls.h"

class System{
public:
    // Constructor setting all the variables of the class
    // we initialize the system
    System();

    //System cannot be copied
    System(System const& ) = delete;

    //function that simulates the motion of a dipole till max_time
    //and stores it in the std::array<std::vector<lmh::Vector2f>, 2> data;
    void simulatev2(const double &max_time);

    double total_kinetic();

    //delete the with "new" allocated MPoints* in the std::vector
    ~System();



private:

    //compute the geometric centre
    lmh::Vector2f geom_centre();

    // colision with the walls
    void collision(Walls &walls);

    //collision() function overloading with Mpoints itself
    //we use sweep and prune method

    void collision();

    //solve the collision between the two
    //MPoints with two indices
    void collision(int const&, int const&);

    //simply checks if the mPoint and the obstacle really collides...
    bool does_collide(const int &i, const int &j);

    //overriding two collision() function to solve
    //the collision with the obstacles
    void collision(int const&, Obstacle*);

    //method that computes the position, the velocity
    //using the RK4 method
    void compute_RK4(std::vector<std::array<lmh::Vector2f, 5>>&, std::vector<std::array<lmh::Vector2f, 5>> &,
    std::vector<std::array<lmh::Vector2f, 2>> & );

    /*
     * Function that configure the initial configuration
     * */
    void config_1();



    /*
     * DATA
     */

    //time increment
    double dt = 0.01;
    double WIDTH = 1920;
    double HEIGHT = 1080;
    double offset = 20;



    // the mass points
    // and the springs
    std::vector<MPoint*> mPoints;
    std::vector<Spring> springs;
    std::vector<Obstacle> obstacles;

};



#endif //SOFT_BODY_SIMULATOR_SYSTEM_H
