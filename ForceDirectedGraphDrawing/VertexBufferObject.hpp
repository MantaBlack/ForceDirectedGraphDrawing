#pragma once

#include "IBufferObject.hpp"

class VertexBufferObject : public IBufferObject
{
public:
    VertexBufferObject(GLfloat* vertices,
        GLsizeiptr size,
        GLenum usage);

    ~VertexBufferObject();

    void bind() override;
    void unbind() override;
    void release() override;

    void update(GLfloat* vertices, GLsizeiptr size, GLenum usage);
};