#pragma once

#include <glad/glad.h>

class IBufferObject
{
protected:
    GLuint m_id = 0;

public:
    virtual ~IBufferObject() = default;

    virtual void bind() = 0;
    virtual void unbind() = 0;
    virtual void release() = 0;
};