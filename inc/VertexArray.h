
#ifndef SOFT_BODY_SIMULATOR_VERTEXARRAY_H
#define SOFT_BODY_SIMULATOR_VERTEXARRAY_H
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"

class VertexArray{
public:
    VertexArray();
    ~VertexArray();

    void add_buffer(const VertexBufferLayout&, const VertexBufferLayout&);


private:

};

#endif //SOFT_BODY_SIMULATOR_VERTEXARRAY_H
