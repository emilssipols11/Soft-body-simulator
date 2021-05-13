#include <Window.h>


Window::Window(const unsigned int &h, const unsigned int &w) {
    //create the GLFWwindow
    //GLFWwindow is a pointer, thus n is a pointer to a pointer


    win = new GLFWwindow*;

    if (!glfwInit()){
        std::cerr<<"Unable to initialize glfw\n"
                   <<"aborting the program";
        exit(-1);
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    *win = glfwCreateWindow(1920, 1080, "GLFW Window", NULL, NULL);
    glfwMakeContextCurrent(*win);

    if(!*win){
        glfwTerminate();
        exit(-1);
    }


    if(glewInit()!=GLEW_OK){
        std::cerr<<"glew initialized incorrectly\n";
        exit(-1);
    }



}

bool Window::window_closed() {
    glfwWindowShouldClose(*win);
}

void Window::terminate_window() {
    glfwTerminate();
}

void Window::swap_buffers() {
    glfwSwapBuffers(*win);
}

void Window::poll_events() {
    glfwPollEvents();
}

void Window::print_used_GPU() {
    const unsigned char* vendor = glGetString(GL_VENDOR); // Returns the vendor
    const unsigned char* renderer = glGetString(GL_RENDERER); // Returns a hint to the model

    std::cout<<"The GPU vendor :\t"<<vendor<<std::endl;
    std::cout<<"The GPU renderer :\t"<<renderer<<std::endl;

}