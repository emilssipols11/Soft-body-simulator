#ifndef SOFT_BODY_SIMULATOR_SHADER_H
#define SOFT_BODY_SIMULATOR_SHADER_H
#include <string>
#include <iostream>
#include <fstream>

class Shader{
public:
    //the id of the programm
    unsigned int ID;

    //pass the file arguments
    Shader(const std::string& vertexsh, const std::string& fragmentsh);


private:
    std::string vertex_shader;
    std::string fragment_shader;

};

#endif //SOFT_BODY_SIMULATOR_SHADER_H
