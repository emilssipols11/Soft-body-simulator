//
// Created by leo on 4/20/21.
//

#ifndef SOFT_BODY_SIMULATOR_SPRING_H
#define SOFT_BODY_SIMULATOR_SPRING_H

class Spring{
public:
    //Constructor setting all the variables of the class
    //the actual length of the spring must be specified separately
    // - it is set to l0 in the constructor
    Spring(const double& k, const double& damping, const double& l0);


    double gLen() const;

    void sLen(const double& l);


private:
    //length
    double l;

    //rigidness and damping
    double k;
    double damping;

    //default length (without any force applied)
    double l0;

};

#endif //SOFT_BODY_SIMULATOR_SPRING_H
