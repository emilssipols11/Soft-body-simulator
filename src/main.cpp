#include <iostream>
#include "Vector2f.h"
#include "Dipole.h"
#include "System.h"
#include <vector>
#include <fstream>
#include "Window.h"
#include <cmath>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "VertexArray.h"
#include "Shader.h"

//void simulate();

static void cosine();


const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "uniform vec3 offSet;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(-aPos.x + offSet.x, -aPos.y + offSet.y, -aPos.z + offSet.z, 1.0);\n"
                                 "}\0";


const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(0.0f, 1.0f, 0.0f, 1.0f );\n"
                                   "}\0";



int main() {
    MPoint points[2]  {
            MPoint(lmh::Vector2f(0.0,0.0), lmh::Vector2f(0.0,0.0), lmh::Vector2f(0.0, 0.0), 5000),
            MPoint(lmh::Vector2f(14.0,10.0), lmh::Vector2f(0.0,5.0), lmh::Vector2f(0.0, 0.0), 5)
    };
    Spring spr(100.0, 0 , 10.0);

    Dipole dip(points[1], points[0], spr );

    System sys;
    sys.simulate(10.0);




    float positions[]={
            -0.5f, -0.5f,
            0.5f, -0.5f,
            0.5f, 0.5f,
    };

    Window w(600,900);

    w.print_used_GPU();


    Shader sh("/home/leo/Documents/projects/cpp_projects/Soft-body-simulator/src/shaders/vshader.glsl" ,"/home/leo/Documents/projects/cpp_projects/Soft-body-simulator/src/shaders/fshader.glsl");
    sh.compile_and_link();
    sh.use();

    VertexArray va;
    va.bind();

    VertexBuffer vb(positions, sizeof(positions));
    vb.bind();
    va.add_buffer(vb);


    while (!w.window_closed()){

        va.bind();

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawArrays(GL_TRIANGLES, 0,3);

        w.swap_buffers();
        w.poll_events();
    }

    w.terminate_window();

    return 0;
}

void cosine(){
    std::ofstream file("../cosine.txt");
    double time = 0.0;
    double dt = 0.01;
    while (time<10.0){
        file <<time<<"\t"<<10.0+2.0* cos(10*time)<<"\n";
        time +=dt;
    }

    file.close();

}