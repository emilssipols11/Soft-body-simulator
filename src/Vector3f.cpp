#include "Vector3f.h"
#include <iostream>
#include <cmath>


/**
 *
 * CONSTRUCTORS
 *
 * **/
lmh::Vector3f::Vector3f(const double &x, const double &y, const double &z) : x(x), y(y), z(z) {

    #ifdef DEBUG_CONSTRUCTORS
    std::cout<<"Default constructor called\n";
    #endif

}

lmh::Vector3f::Vector3f(const Vector3f &vec) {
    this->x = vec.x;
    this->y = vec.y;
    this->z = vec.z;

#ifdef DEBUG_CONSTRUCTORS
    std::cout<<"Copy constructor called\n";
#endif
}

lmh::Vector3f::Vector3f(Vector3f &&vec) noexcept {
    this->x = vec.x;
    this->y = vec.y;
    this->z = vec.z;

#ifdef DEBUG_CONSTRUCTORS
    std::cout<<"Rvalue constructor called\n";
#endif
}

/**
 *
 * GETTERS AND SETTERS
 *
 * **/

double lmh::Vector3f::gX() const {
    return this->x;
}

double lmh::Vector3f::gY() const {
    return this->y;
}

double lmh::Vector3f::gZ() const {
    return this->z;
}

void lmh::Vector3f::sX(const double &x) {
    this->x = x;
}

void lmh::Vector3f::sY(const double &y){
    this->y = y;
}

void lmh::Vector3f::sZ(const double &z){
    this->z = z;
}

/**
 *
 * MATHEMATICAL
 *
 * **/

double lmh::Vector3f::norm() const{
    return sqrt(x*x + y*y + z*z);
}

double lmh::Vector3f::dot(const Vector3f& vec) const {
    return ( this->x * vec.x + this->y * vec.y + this->z * vec.z );
}

lmh::Vector3f lmh::Vector3f::normalize(const Vector3f &vec) const {
    return Vector3f((*this)*(1/(this->norm())));
}
/**
 *
 * OPERATORS
 *
 * **/
lmh::Vector3f lmh::Vector3f::operator+(const Vector3f &vec) const {
    return {this->x + vec.x , this->y + vec.y , this->z + vec.z};
}

lmh::Vector3f& lmh::Vector3f::operator+=(const Vector3f &vec)  {
    this->x += vec.x;
    this->y += vec.y;
    this->z += vec.z;
    return *this ;
}

lmh::Vector3f& lmh::Vector3f::operator -= (const Vector3f& vec){
    this->x -= vec.x;
    this->y -= vec.y;
    this->z -= vec.z;
    return *this ;
} ;


lmh::Vector3f lmh::Vector3f::operator-(const lmh::Vector3f &vec) const {
    return {this->x - vec.x , this->y - vec.y , this->z - vec.z};
}

lmh::Vector3f lmh::Vector3f::operator*(const double &lambda) const {
    return {this->x * lambda , this->y * lambda , this->z * lambda};
}

lmh::Vector3f operator * (const double& lambda, const lmh::Vector3f& vec) {
    return {vec.gX() * lambda , vec.gY() * lambda , vec.gZ() * lambda};
}

lmh::Vector3f& lmh::Vector3f::operator*=(const double &lambda) {
    this->x *= lambda;
    this->y *= lambda;
    this->z *= lambda;
    return *this ;
}

std::ostream& lmh::operator << ( std::ostream& stream, const lmh::Vector3f& vec){
    stream<<"("<<vec.gX() <<", "<<vec.gY()<<", "<<vec.gZ()<<")\n";
    return stream;
}


/**
 *
 * ASSIGNMENT OPERATORS
 *
 * **/

lmh::Vector3f& lmh::Vector3f::operator=(const Vector3f &vec) {
     this->x = vec.x;
     this->y = vec.y;
     this->z = vec.z;

#ifdef DEBUG_CONSTRUCTORS
    std::cout<<"Copy assigment called\n";
#endif

     return (*this);
}

lmh::Vector3f& lmh::Vector3f::operator=(Vector3f &&vec) noexcept {
    this->x = vec.x;
    this->y = vec.y;
    this->z = vec.z;

#ifdef DEBUG_CONSTRUCTORS
    std::cout<<"Move assigment called\n";
#endif

    return (*this);
 }


