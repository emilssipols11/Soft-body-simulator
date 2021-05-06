#include <Window.h>


Window::Window(const unsigned int &h, const unsigned int &w) {
    //create the GLFWwindow
    //GLFWwindow is a pointer, thus n is a pointer to a pointer

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, 3);
    win = new GLFWwindow*;

    if (!glfwInit()){
        std::cerr<<"Unable to initialize glfw\n"
                   <<"aborting the program";
        exit(-1);
    }


    *win = glfwCreateWindow(600, 200, "GLFW Window", NULL, NULL);

    if(!*win){
        glfwTerminate();
    }

    glfwMakeContextCurrent(*win);

    if(glewInit()!=GLEW_OK){
        std::cerr<<"glew initialized incorrectly\n";
    }



}

bool Window::window_closed() {
    glfwWindowShouldClose(*win);
}

void Window::terminate_window() {
    glfwTerminate();
}
