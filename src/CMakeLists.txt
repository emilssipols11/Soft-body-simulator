cmake_minimum_required(VERSION 3.16)
#project(Soft-body-simulator)

project(Sources)

set(CMAKE_CXX_STANDARD 17)

add_executable(Sources main.cpp
        Vector2f.cpp Vector3f.cpp  MPoint.cpp
        Spring.cpp  Dipole.cpp System.cpp Window.cpp ../inc/Shader.h Shader.cpp)

include_directories(
        "../inc"
        #"${CMAKE_BINARY_DIR}/inc"
)

target_link_libraries(Sources -lglut -lglfw -lGLEW -lGL -lGLU)



#Spring.h Dipole.h System.h MPoint.h

