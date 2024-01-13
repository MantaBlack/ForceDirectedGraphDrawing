#include "VertexArrayObject.hpp"

VertexArrayObject::VertexArrayObject()
{
    glGenVertexArrays(1, &m_id);
}

VertexArrayObject::~VertexArrayObject()
{
    release();
}

void VertexArrayObject::bind()
{
    glBindVertexArray(m_id);
}

void VertexArrayObject::unbind()
{
    glBindVertexArray(0);
}

void VertexArrayObject::release()
{
    glDeleteVertexArrays(1, &m_id);
}

void VertexArrayObject::link_vertex_buffer(IBufferObject& vbo,
    GLuint index,
    GLint size,
    GLenum type,
    GLboolean normalized,
    GLsizei stride,
    const void * offset)
{
    vbo.bind();

    // tell OpenGL how to interpret the buffer
    glVertexAttribPointer(index, size, type, normalized, stride, offset);
    glEnableVertexAttribArray(index);

    vbo.unbind();
}
