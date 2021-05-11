#ifndef SOFT_BODY_SIMULATOR_VERTEXBUFFERLAYOUT_H
#define SOFT_BODY_SIMULATOR_VERTEXBUFFERLAYOUT_H
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

/*
 * DEPRECATED CLASS THAT IS CURRENTLY UNUSED
 */
struct VertexBufferElement{
    unsigned int type;
    unsigned int count;
    bool normalized;

};

class VertexBufferLayout{
public:
    VertexBufferLayout() : stride(0) {};

    //push the element
    //the template to use the type to VertexAttribPointer

    template<typename T = float>
    void push(unsigned int count){
        elements.push_back({GL_FLOAT, count, GL_FALSE});
        this->stride += 4;
    }

    inline unsigned int gStride(){return this->stride;}

    inline const std::vector<VertexBufferElement> & gElements() const {return this->elements;}





private:
    std::vector<VertexBufferElement> elements;
    unsigned int stride;
};

#endif //SOFT_BODY_SIMULATOR_VERTEXBUFFERLAYOUT_H

