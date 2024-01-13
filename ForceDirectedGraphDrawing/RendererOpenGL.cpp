#include "ElementBufferObject.hpp"
#include "RendererOpenGL.hpp"
#include "VertexArrayObject.hpp"
#include "VertexBufferObject.hpp"

void RendererOpenGL::create_window()
{
    // inform GLFW about OpenGL version we are using (OpenGL 3.3)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // tell GLFW that we are using the CORE profile (modern functions only)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(m_width,
        m_height,
        m_title.c_str(),
        NULL,
        NULL);

    if (m_window == NULL)
    {
        glfwTerminate();
        throw std::string("Failed to create window.");
    }

    glfwMakeContextCurrent(m_window);
}

void RendererOpenGL::set_viewport()
{
    glViewport(m_lower_left_x,
        m_lower_left_y,
        m_width,
        m_height);
}

RendererOpenGL::~RendererOpenGL()
{
    release();
}

void RendererOpenGL::render()
{
    // initialize GLFW
    glfwInit();

    // create window
    create_window();

    // load current configuration for OpenGL
    gladLoadGL();

    // tell OpenGL the area of the window to render in
    set_viewport();

    VertexArrayObject vao;
    vao.bind();

    const GLenum buffer_usage = GL_DYNAMIC_DRAW;

    VertexBufferObject vbo(&m_vertices.front(), m_vertices.size(), buffer_usage);

    ElementBufferObject ebo(&m_indices.front(), m_indices.size(), buffer_usage);

    vao.link_vertex_buffer(vbo, 0, DIM, GL_FLOAT, GL_FALSE, 0, (void*)0);

    vao.unbind();
    vbo.unbind();
    ebo.unbind();

    while (!glfwWindowShouldClose(m_window))
    {
        // specify a default background color
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);

        // clear the back buffer and apply the default background color
        glClear(GL_COLOR_BUFFER_BIT);

        vao.bind();

        // use this function when drawing elements with an EBO
        glDrawElements(GL_POINTS, m_vertices.size(), GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(m_window);

        glfwPollEvents();
    }

    vao.release();
    vbo.release();
    ebo.release();

    glfwDestroyWindow(m_window);

    glfwTerminate();
}

void RendererOpenGL::release()
{
    if (m_window != NULL)
    {
        glfwDestroyWindow(m_window);
        m_window = NULL;
    }

    glfwTerminate();
}
