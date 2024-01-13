#include "ElementBufferObject.hpp"
#include "RendererOpenGL.hpp"
#include "VertexArrayObject.hpp"
#include "VertexBufferObject.hpp"
#include "ShaderObject.hpp"
#include "SingleThreadGraphDrawer.hpp"

#include <algorithm>

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

    const GLenum buffer_usage = GL_DYNAMIC_DRAW;

    ShaderObject shader("vertex_shader.glsl", "fragment_shader.glsl");

    /* generate buffer objects for vertices */
    std::vector<GLuint> vertex_indices(m_vertices.size() / DIM);

    // generate indices to use all vertices for rendering points
    std::generate(vertex_indices.begin(),
        vertex_indices.end(),
        [n = 0]() mutable { return n++; });

    VertexArrayObject vertices_vao;
    vertices_vao.bind();

    VertexBufferObject vertices_vbo(&m_vertices.front(), m_vertices.size() * sizeof(GLfloat), buffer_usage);

    ElementBufferObject vertices_ebo(&vertex_indices.front(), vertex_indices.size() * sizeof(GLuint), buffer_usage);

    vertices_vao.link_vertex_buffer(vertices_vbo, 0, DIM, GL_FLOAT, GL_FALSE, 0, (void*)0);

    vertices_vao.unbind();
    vertices_vbo.unbind();
    vertices_ebo.unbind();

    /* generate buffer objects for edges */
    VertexArrayObject edges_vao;
    edges_vao.bind();

    VertexBufferObject edges_vbo(&m_vertices.front(), m_vertices.size() * sizeof(GLfloat), buffer_usage);

    ElementBufferObject edges_ebo(&m_indices.front(), m_indices.size() * sizeof(GLuint), buffer_usage);

    edges_vao.link_vertex_buffer(edges_vbo, 0, DIM, GL_FLOAT, GL_FALSE, 0, (void*)0);

    edges_vao.unbind();
    edges_vbo.unbind();
    edges_ebo.unbind();

    while (!glfwWindowShouldClose(m_window))
    {
        // specify a default background color
        glClearColor(0.f, 0.f, 0.f, 0.f);

        // clear the back buffer and apply the default background color
        glClear(GL_COLOR_BUFFER_BIT);
        glPointSize(10.f);

        shader.activate();

        vertices_vao.bind();
        glDrawElements(GL_POINTS, m_vertices.size(), GL_UNSIGNED_INT, 0);
        
        edges_vao.bind();
        glDrawElements(GL_LINES, m_indices.size(), GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(m_window);

        glfwPollEvents();

        m_graph_drawer.draw_graph(m_vertices);

        vertices_vbo.update(&m_vertices.front(), m_vertices.size() * sizeof(GLfloat), buffer_usage);
        vertices_vao.link_vertex_buffer(vertices_vbo, 0, DIM, GL_FLOAT, GL_FALSE, 0, (void*)0);
    }

    vertices_vao.release();
    vertices_vbo.release();
    vertices_ebo.release();

    edges_vao.release();
    edges_vbo.release();
    edges_ebo.release();

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
