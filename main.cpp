#include <iostream>
#include "Vector2f.h"
#include "Vector3f.h"

int main() {
    lmh::Vector2f vector(3, 5);
    lmh::Vector2f vector2(1,1);

    lmh::Vector3f vector3(2,2,3);
    lmh::Vector3f vector4(lmh::Vector3f(4,4,4));
    vector4 = vector3*3.0;
    std::cout<<vector;


    return 0;
}
