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

    //pass the file arguments
    Shader(const std::string& vertexsh, const std::string& fragmentsh);

    //compile and link the shaders
    void compile_and_link();

    //use the shader program
    void use();

    unsigned int gID() const;

    //sets the new uniform to the shader
    void sUniformVec3(const std::string& name, const float& x, const float& y, const float& z = 0.0f);

private:
    std::string vertex_shader;
    std::string fragment_shader;
    unsigned int ID;


};

#endif //SOFT_BODY_SIMULATOR_SHADER_H
