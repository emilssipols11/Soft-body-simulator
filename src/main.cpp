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
    cosine();
    std::cout<<"ICCE\n";



    Window w(600,900);

    w.print_used_GPU();

    while (!w.window_closed()){

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