//
// Created by leo on 5/11/21.
//

#ifndef SOFT_BODY_SIMULATOR_INDEXBUFFER_H
#define SOFT_BODY_SIMULATOR_INDEXBUFFER_H

class IndexBuffer{
public:
    //data* - the array of indices
    //count - the number of indices
    IndexBuffer(const unsigned int* data, unsigned int count);

    //delete the indices
    ~IndexBuffer();


    void bind() const;

    void unbind() const;

    unsigned int gCount();

private:
    unsigned int vebID;
    unsigned int count;
};

#endif //SOFT_BODY_SIMULATOR_INDEXBUFFER_H
