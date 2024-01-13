#pragma once

#include "IBufferObject.hpp"

class VertexBufferObject : public IBufferObject
{
    VertexBufferObject(GLfloat* vertices,
        GLsizeiptr size,
        GLenum usage);

    ~VertexBufferObject();

    void bind() override;
    void unbind() override;
    void release() override;
};