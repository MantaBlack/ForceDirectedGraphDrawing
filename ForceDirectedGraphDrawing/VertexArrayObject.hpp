#pragma once

#include "IBufferObject.hpp"
#include "VertexBufferObject.hpp"

class VertexArrayObject : public IBufferObject
{
public:
    VertexArrayObject();

    ~VertexArrayObject();

    void bind() override;
    void unbind() override;
    void release() override;

    void link_vertex_buffer(IBufferObject& vbo,
        GLuint index,
        GLint size,
        GLenum type,
        GLboolean normalized,
        GLsizei stride,
        const void* offset);
};