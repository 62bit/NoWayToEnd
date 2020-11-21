#include "vertexBuffer.h"

void GenerateVertexBuffer(vertex_buffer &vb)
{
    glGenBuffers(1, &vb.bufferID);
    glBindBuffer(GL_ARRAY_BUFFER, vb.bufferID);
    glBufferData(GL_ARRAY_BUFFER, vb.size, (float *)vb.vertices, GL_STATIC_DRAW);
}

void SetAttributeF(const vertex_buffer &vb, unsigned int index, int size, int32_t stride, const void *pointer)
{
    glBindBuffer(GL_ARRAY_BUFFER, vb.bufferID);
    glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, pointer);
    glEnableVertexAttribArray(index);
}
