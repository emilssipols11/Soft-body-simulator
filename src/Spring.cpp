//
// Created by leo on 4/20/21.
//

#include "Spring.h"

Spring::Spring(const double &k, const double& damping,const double &l0) : k(k), damping(damping), l0(l0) {

    lines.resize(2);
    lines.setPrimitiveType(sf::LineStrip);
    lines[0].color = sf::Color::Red;
    lines[1].color = sf::Color::Red;

    this->is_drawed = false;

}

double Spring::gLen() const {
    return lmh::Vector2f(this->A->gPos() - this->B->gPos()).norm();
}

void Spring::sA( MPoint* a) {
    this->A = a;
}

void Spring::sB( MPoint *b) {
    this->B = b;
}

double Spring::gK() const {
    return this->k;
}

lmh::Vector2f Spring::compute_force() {
    lmh::Vector2f F = (B->gPos() - A->gPos());
    F = (F.normalize(F)*(-l0+F.norm()))*(k);
    return F;

}

double Spring::gl0() const {
    return l0;
}

MPoint* Spring::gA() const {
    return this->A;
}

MPoint* Spring::gB() const{
    return this->B;
}

void Spring::draw(sf::RenderWindow *w) {
        lines[0].position = sf::Vector2f(this->A->gPos().gX(), this->A->gPos().gY());
        lines[1].position = sf::Vector2f(this->B->gPos().gX(), this->B->gPos().gY());
        w->draw(lines);
}

double Spring::gEnergy() const {
    return  ((this->A->gPos() - this->B->gPos()).norm() - this->l0) *
            ((this->A->gPos() - this->B->gPos()).norm() - this->l0)   * this->k * 0.5;
}

