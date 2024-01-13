#pragma once

#include <glad/glad.h>
#include <vector>

class IGraphDrawer
{
public:
    virtual ~IGraphDrawer() = default;

    virtual void draw_graph(std::vector<GLfloat>& vertices) = 0;
};