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
#include "IndexBuffer.h"

//void simulate();

static void cosine();


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
            -0.5f, -0.5f, 0.0f,
            -0.5f, 0.5f, 0.0f,
            0.5f, 0.5f, 0.0f,
            0.5f, -0.5f, 0.0f
            //0.5f, 0.5f, 0.0f,
            //0.5f, -0.5f, 0.0f,
            //-0.5f, 0.5f, 0.0f
    };

    unsigned int indices[]{
        0,1,2,
        2,3,0
    };

    Window w(640,480);

    Shader sh("/home/leo/Documents/projects/cpp_projects/Soft-body-simulator/src/shaders/vshader.glsl" ,"/home/leo/Documents/projects/cpp_projects/Soft-body-simulator/src/shaders/fshader.glsl");
    sh.compile_and_link();
    sh.use();

    VertexArray va;
    va.bind();

    VertexBuffer vb(positions, sizeof(positions));
    vb.bind();

    IndexBuffer ib(indices, sizeof(indices));

    ib.bind();

    va.add_buffer(vb);


    while (!w.window_closed()){


        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
        //glDrawArrays(GL_LINES, 0,2);

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