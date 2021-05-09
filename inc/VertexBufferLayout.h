#ifndef SOFT_BODY_SIMULATOR_VERTEXBUFFERLAYOUT_H
#define SOFT_BODY_SIMULATOR_VERTEXBUFFERLAYOUT_H
#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct VertexBufferElement{
    unsigned int type;
    unsigned int count;
    bool normalized;

};

class VertexBufferLayout{
public:
    VertexBufferLayout();

    //push the element
    //the template to use the type to VertexAttribPointer

    template<typename T>
    void push(int count){
        static_assert(false);
    }

    template<>
    void push<float>(int count, bool normalized = false){
        elements.push_back({GL_FLOAT, count, normalized});
        this->stride+=sizeof(GLfloat);
    }

    template<>
    void push<unsigned int>(int count, bool normalized = false){
        this->elements.push_back({GL_UNSIGNED_INT, count, normalized});
        this->stride+=sizeof(GLuint);
    }

    template<>
    void push<unsigned char>(int count, bool normalized = false){
        elements.push_back({GL_UNSIGNED_BYTE, count, normalized});
        this->stride+=sizeof(GLbyte);
    }

    inline const& std::vector<VertexBufferElement> get_elements() const { return this->elements; }
    inline unsigned int get_stride() const {return this->stride;}


private:
    std::vector<VertexBufferElement> elements;
    unsigned int stride;
};

#endif //SOFT_BODY_SIMULATOR_VERTEXBUFFERLAYOUT_H

