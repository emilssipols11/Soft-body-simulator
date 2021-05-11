#include "Shader.h"


Shader::Shader(const std::string &vertexsh, const std::string& fragmentsh) {
//loading the shaders to the files

std::ifstream vert;
std::stringstream vertexStream;

    vert.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        //open file and put it in the std::string vertex_shader
        vert.open(vertexsh);
        vertexStream<<vert.rdbuf();
        vert.close();

        this->vertex_shader = vertexStream.str();
    }
    //handle errors due to reading
    catch(std::ifstream::failure &e){
        std::cerr<<"ERROR::VSHADER::NOT READ SUCCESSFULLY\n";
    }

    //similarly for the fragment shader
    std::ifstream frag;
    std::stringstream fragmentStream;

    frag.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {

        frag.open(fragmentsh);
        fragmentStream<<frag.rdbuf();
        frag.close();

        this->fragment_shader = fragmentStream.str();
    }
    //handle errors due to reading
    catch(std::ifstream::failure &e){
        std::cerr<<"ERROR::VSHADER::NOT READ SUCCESSFULLY\n";
    }

}

void Shader::compile_and_link() {
    /*
     * compile both shaders
     */
    unsigned int vertexID, fragmentID;
    int success;
    char info[512];



    const char* vShaderCode = vertex_shader.c_str();
    const char*  fShaderCode = fragment_shader.c_str();


    //std::cout<<""<<std::endl;
    vertexID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexID, 1, &vShaderCode, NULL);
    glCompileShader(vertexID);

    glGetShaderiv(vertexID, GL_COMPILE_STATUS, &success);

    //handle errors
    if(!success){
        glGetShaderInfoLog(vertexID, 512, NULL, info );
        std::cerr<<"ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"<<info<<std::endl;
    }

    fragmentID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentID, 1, &fShaderCode, NULL);
    glCompileShader(fragmentID);

    glGetShaderiv(fragmentID, GL_COMPILE_STATUS, &success);

    //handle errors
    if (!success){
        glGetShaderInfoLog(fragmentID, 512, NULL, info);
        std::cerr<<"ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"<<info<<std::endl;
    }

    /*
     * link with the program-containing both vertex and fragment shaders
     */

    this->ID = glCreateProgram();
    glAttachShader(this->ID, vertexID);
    glAttachShader(this->ID, fragmentID);

    glLinkProgram(this->ID);

    glGetProgramiv(this->ID, GL_LINK_STATUS, &success);

    //handle errors
    if(!success){
        glGetProgramInfoLog(this->ID, 512, NULL, info);
        std::cerr<<"ERROR::SHADER::PROGRAM::LINKING_FAILED\n"<<info<<std::endl;
    }

    /*
     * once linked we delete the shaders
     */
    glDeleteShader(vertexID);
    glDeleteShader(fragmentID);

}

void Shader::use() {
    glUseProgram(this->ID);
}

unsigned int Shader::gID() const {
    return this->ID;
}

void Shader::sUniformVec3(const std::string &name, const float &x, const float &y, const float &z) {
    int vertexColorLocation = glGetUniformLocation(this->ID, name.c_str());
    glUniform3f(vertexColorLocation, x, y, z);
}
