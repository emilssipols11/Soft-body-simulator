#include "Shader.h"


Shader::Shader(const std::string &vertexsh, const std::string& fragmentsh) {
//loading the shaders to the files
    std::ifstream vert(vertexsh);

    if(!vert.is_open()){
        std::cerr<<"Vertex Shader file not open\n"<<
                   "exiting\n";
        exit(-1);
    } else{
        std::string temp;
        while (std::getline(vert, temp)){
            this->vertex_shader+=temp;
        }
    }

    vert.close();

    std::ifstream frag(fragmentsh);

    if(!frag.is_open()){
        std::cerr<<"Fragment Shader file not open\n"<<
                 "exiting\n";
        exit(-1);
    } else{
        std::string temp;
        //pushing the file to th string
        while (std::getline(frag, temp)){
            this->fragment_shader+=temp;
        }
    }

}
