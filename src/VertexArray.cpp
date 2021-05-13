#include "VertexArray.h"

VertexArray::VertexArray() {
    //we generate ONE VertexArray
    glGenVertexArrays(1, &vaoID);


}

void VertexArray::add_buffer( VertexBuffer & vb) {
    vb.bind();
    unsigned int offset = 0;

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT,
                          GL_FALSE, 3*sizeof(float), (const void *)0);


}

VertexArray::~VertexArray() {
    glDeleteVertexArrays(1, &vaoID);
}

void VertexArray::bind() const {
    glBindVertexArray(vaoID);
}

void VertexArray::unbind() const {
    glBindVertexArray(0);
}
