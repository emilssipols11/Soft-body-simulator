cmake_minimum_required(VERSION 3.16)
project(Soft-body-simulator)

set(CMAKE_CXX_STANDARD 17)


add_executable(Soft-body-simulator main.cpp Vector2f.cpp Vector3f.cpp MPoint.h MPoint.cpp Spring.cpp Spring.h Dipole.h Dipole.cpp)