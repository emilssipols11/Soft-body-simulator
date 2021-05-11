//
// Created by leo on 5/11/21.
//

#include <IndexBuffer.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

IndexBuffer::IndexBuffer(const unsigned int *data, unsigned int count) : count(count) {
    glGenBuffers(1, &vebID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vebID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(GLuint), data, GL_DYNAMIC_DRAW);
}

IndexBuffer::~IndexBuffer() {
    glDeleteBuffers(1, &vebID);
}

void IndexBuffer::bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, vebID);
}

void IndexBuffer::unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

unsigned int IndexBuffer::gCount() {
    return this->count;
}