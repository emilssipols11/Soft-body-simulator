#ifndef SOFT_BODY_SIMULATOR_WINDOW_H
#define SOFT_BODY_SIMULATOR_WINDOW_H
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Window{
public:
    Window(const unsigned int&h, const unsigned int&w);
    bool window_closed();
    void terminate_window();
    void swap_buffers();
    void poll_events();
    void print_used_GPU();
private:
    GLFWwindow** win;
};


#endif //SOFT_BODY_SIMULATOR_WINDOW_H
