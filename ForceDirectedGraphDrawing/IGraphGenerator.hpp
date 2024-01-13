#pragma once

#include <glad/glad.h>

#include <vector>

class IGraphGenerator
{
public:
    virtual ~IGraphGenerator() = default;

    virtual void get_graph(std::vector<GLfloat>& vertices, std::vector<GLuint>& edges) = 0;
};