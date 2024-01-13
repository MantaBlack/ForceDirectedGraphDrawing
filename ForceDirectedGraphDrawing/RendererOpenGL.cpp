#include "RendererOpenGL.hpp"

RendererOpenGL::~RendererOpenGL()
{
    release();
}

void RendererOpenGL::render()
{
}

void RendererOpenGL::release()
{
    glfwDestroyWindow(m_window);
    glfwTerminate();

    m_window = nullptr;
}
