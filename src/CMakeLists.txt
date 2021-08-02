cmake_minimum_required(VERSION 3.16)
#project(Soft-body-simulator)

project(Sources)

set(CMAKE_CXX_STANDARD 17)

add_executable(Sources main.cpp
        Vector2f.cpp Vector3f.cpp  MPoint.cpp
        Spring.cpp  Dipole.cpp System.cpp Window.cpp ../inc/Shader.h Shader.cpp VertexBuffer.cpp ../inc/VertexBuffer.h ../inc/VertexArray.h VertexArray.cpp VertexBufferLayout.cpp ../inc/VertexBufferLayout.h IndexBuffer.cpp ../inc/IndexBuffer.h Walls.cpp ../inc/Walls.h Obstacle.cpp ../inc/Obstacle.h)

include_directories(
        "../inc"
        #"${CMAKE_BINARY_DIR}/inc"
)

target_link_libraries(Sources -lglfw -lGLEW -lGL -lGLU -lsfml-graphics -lsfml-window -lsfml-system)



#Spring.h Dipole.h System.h MPoint.h

