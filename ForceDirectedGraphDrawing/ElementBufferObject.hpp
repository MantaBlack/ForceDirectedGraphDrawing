#pragma once

#include "IBufferObject.hpp"

class ElementBufferObject : public IBufferObject
{
public:
    ElementBufferObject(GLuint* indices,
        GLsizeiptr size,
        GLenum usage);
    
    ~ElementBufferObject();

    void bind() override;
    void unbind() override;
    void release() override;
};