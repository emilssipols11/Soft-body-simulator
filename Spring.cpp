//
// Created by leo on 4/20/21.
//

#include "Spring.h"

Spring::Spring(const double &k, const double& damping,const double &l0) : k(k), damping(damping), l0(l0) {

}

double Spring::gLen() const {
    return lmh::Vector2f(this->A.gPos() - this->B.gPos()).norm();
}

void Spring::sA(const MPoint &a) {
    this->A = a;
}

void Spring::sB(const MPoint &b) {
    this->B = b;
}

lmh::Vector2f Spring::compute_force() {
    lmh::Vector2f F = (B.gPos() - A.gPos());
    F = (F.normalize(F)*(-l0+F.norm()))*(k);
    return F;

}

