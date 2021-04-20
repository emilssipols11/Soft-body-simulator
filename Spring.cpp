//
// Created by leo on 4/20/21.
//

#include "Spring.h"

Spring::Spring(const double &k, const double& damping,const double &l0) : k(k), damping(damping), l0(l0) {

}

double Spring::gLen() const {
    return this->l;
}

void Spring::sLen(const double &l) {
    this->l = l;
}

