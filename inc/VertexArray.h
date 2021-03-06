
#ifndef SOFT_BODY_SIMULATOR_VERTEXARRAY_H
#define SOFT_BODY_SIMULATOR_VERTEXARRAY_H
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"


class VertexArray{
public:
    //generation
    VertexArray();

    //deletion
    ~VertexArray();

    //hardcoded version of VertexAttribPointer
    void add_buffer( VertexBuffer&);
    void bind() const;
    void unbind() const;


private:

    unsigned int vaoID;

};

#endif //SOFT_BODY_SIMULATOR_VERTEXARRAY_H
