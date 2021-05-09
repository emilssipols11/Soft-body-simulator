#ifndef SOFT_BODY_SIMULATOR_VERTEXBUFFER_H
#define SOFT_BODY_SIMULATOR_VERTEXBUFFER_H

class VertexBuffer{

public:
    //the constructor receives a pointer to data that it will contain
    VertexBuffer(const void* data, unsigned int size);

    //binder and unbinder
    void bind();
    void unbind();


    ~VertexBuffer();



private:
    unsigned int vboID;

};


#endif //SOFT_BODY_SIMULATOR_VERTEXBUFFER_H
