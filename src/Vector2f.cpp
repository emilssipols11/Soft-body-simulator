#include "Vector2f.h"
#include <iostream>
#include <cmath>
#include <utility>


/**
 *
 * CONSTRUCTORS
 *
 * **/
lmh::Vector2f::Vector2f(const double &x, const double &y) : x(x), y(y){

    #ifdef DEBUG_CONSTRUCTORS
    std::cout<<"Default constructor called\n";
    #endif

}

lmh::Vector2f::Vector2f(const Vector2f &vec) {
    this->x = vec.x;
    this->y = vec.y;

#ifdef DEBUG_CONSTRUCTORS
    std::cout<<"Copy constructor called\n";
#endif
}

lmh::Vector2f::Vector2f(Vector2f &&vec) noexcept {
    this->x = vec.x;
    this->y = vec.y;

#ifdef DEBUG_CONSTRUCTORS
    std::cout<<"Rvalue constructor called\n";
#endif
}

/**
 *
 * GETTERS AND SETTERS
 *
 * **/

double lmh::Vector2f::gX() const {
    return this->x;
}

double lmh::Vector2f::gY() const {
    return this->y;
}


void lmh::Vector2f::sX(const double &x) {
    this->x = x;
}

void lmh::Vector2f::sY(const double &y){
    this->y = y;
}


/**
 *
 * MATHEMATICAL
 *
 * **/

double lmh::Vector2f::norm() const{
    return sqrt(x*x + y*y );
}

double lmh::Vector2f::dot(const Vector2f& vec) const {
    return ( this->x * vec.x + this->y * vec.y );
}

lmh::Vector2f lmh::Vector2f::normalize(const Vector2f &vec) const {
    lmh::Vector2f ret = (vec)*(1/(this->norm()));
    return ret;
}
/**
 *
 * OPERATORS
 *
 * **/
lmh::Vector2f lmh::Vector2f::operator+(const Vector2f &vec) const {
    return {this->x + vec.x , this->y + vec.y};
}

lmh::Vector2f& lmh::Vector2f::operator+=(const Vector2f &vec)  {
    this->x += vec.x;
    this->y += vec.y;
    return *this ;
}

lmh::Vector2f& lmh::Vector2f::operator -= (const Vector2f& vec){
    this->x -= vec.x;
    this->y -= vec.y;
    return *this ;
} ;


lmh::Vector2f lmh::Vector2f::operator-(const lmh::Vector2f &vec) const {
    return {this->x - vec.x , this->y - vec.y };
}

lmh::Vector2f lmh::Vector2f::operator*(const double &lambda) const {
    return {this->x * lambda , this->y * lambda };
}


lmh::Vector2f& lmh::Vector2f::operator*=(const double &lambda) {
    this->x *= lambda;
    this->y *= lambda;
    return *this ;
}

std::ostream& lmh::operator << ( std::ostream& stream, const lmh::Vector2f& vec){
    stream<<"("<<vec.gX() <<", "<<vec.gY()<<")\n";
    return stream;
}


/**
 *
 * ASSIGNMENT OPERATORS
 *
 * **/

lmh::Vector2f& lmh::Vector2f::operator=(const Vector2f &vec) {
     this->x = vec.x;
     this->y = vec.y;

#ifdef DEBUG_CONSTRUCTORS
    std::cout<<"Copy assigment called\n";
#endif

     return (*this);
}

lmh::Vector2f& lmh::Vector2f::operator=(Vector2f &&vec) noexcept {

    this->x = vec.x;
    this->y = vec.y;

#ifdef DEBUG_CONSTRUCTORS
    std::cout<<"Move assigment called\n";
#endif

    return (*this);
 }

lmh::Vector2f lmh::Vector2f::normalize() {
    double norm = this->norm();
    this->x = (this->x)*(1/norm);
    this->y = (this->y)*(1/norm);
    return (*this);
}



