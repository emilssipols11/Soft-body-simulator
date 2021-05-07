#ifndef SOFT_BODY_SIMULATOR_SHADER_H
#define SOFT_BODY_SIMULATOR_SHADER_H
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Shader{
public:
    //the id of the programm
    unsigned int ID;

    //pass the file arguments
    Shader(const std::string& vertexsh, const std::string& fragmentsh);

    //compile and link the shaders
    void compile_and_link();

    //use the shader program
    void use();

private:
    std::string vertex_shader;
    std::string fragment_shader;


};

#endif //SOFT_BODY_SIMULATOR_SHADER_H
