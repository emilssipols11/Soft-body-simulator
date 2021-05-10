#include "VertexBuffer.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>

VertexBuffer::VertexBuffer(const void *data, unsigned int size) {
    glGenBuffers(1, &vboID);
    glBindBuffer(GL_ARRAY_BUFFER, this->vboID);
    //Static or Dynamic draw (can be modified)
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);

}

void VertexBuffer::bind() {
    glBindBuffer(GL_ARRAY_BUFFER, this->vboID);
}

void VertexBuffer::unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

VertexBuffer::~VertexBuffer() {
    glDeleteBuffers(1, &(this->vboID));
}