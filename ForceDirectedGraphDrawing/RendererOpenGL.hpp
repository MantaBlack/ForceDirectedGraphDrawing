#pragma once

#include "IRenderer.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>

class RendererOpenGL : public IRenderer
{
private:
    const GLuint DIM = 2;

    int m_width;
    int m_height;
    std::string m_title;
    GLint m_lower_left_x;
    GLint m_lower_left_y;

    std::vector<GLfloat> m_vertices;
    std::vector<GLuint> m_indices;

    GLFWwindow* m_window;

    void create_window();
    void set_viewport();

public:
    RendererOpenGL(int width,
        int height,
        std::string title,
        GLint lower_left_x,
        GLint lower_left_y,
        std::vector<GLfloat> vertices,
        std::vector<GLuint> indices)
        : m_width(width),
        m_height(height),
        m_title(title),
        m_lower_left_x(lower_left_x),
        m_lower_left_y(lower_left_y),
        m_vertices(vertices),
        m_indices(indices),
        m_window(NULL)
    {}

    ~RendererOpenGL();

    void render() override;
    void release();
};
