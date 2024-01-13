#include "ElementBufferObject.hpp"

ElementBufferObject::ElementBufferObject(GLuint* indices,
    GLsizeiptr size,
    GLenum usage)
{
    glGenBuffers(1, &m_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, usage);
}

ElementBufferObject::~ElementBufferObject()
{
    release();
}

void ElementBufferObject::bind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}

void ElementBufferObject::unbind()
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void ElementBufferObject::release()
{
    glDeleteBuffers(1, &m_id);
}

