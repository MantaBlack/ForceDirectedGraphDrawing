#include "VertexBufferObject.hpp"

VertexBufferObject::VertexBufferObject(GLfloat* vertices,
    GLsizeiptr size,
    GLenum usage)
{
    glGenBuffers(1, &m_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, usage);
}

VertexBufferObject::~VertexBufferObject()
{
    release();
}

void VertexBufferObject::bind()
{
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void VertexBufferObject::unbind()
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBufferObject::release()
{
    glDeleteBuffers(1, &m_id);
}
