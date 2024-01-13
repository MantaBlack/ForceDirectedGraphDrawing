#include "GridGraphGenerator.hpp"
#include "RendererOpenGL.hpp"
#include "SingleThreadGraphDrawer.hpp"

#include <iostream>
#include <string>
#include <vector>

int main()
{
    const int WINDOW_WIDTH = 1000;
    const int WINDOW_HEGHT = 1000;
    const int VIEWPORT_X = 0;
    const int VIEWPORT_Y = 0;

    const std::size_t NUM_VERTICES_X = 10;
    const std::size_t NUM_VERTICES_Y = 10;
    const GLfloat MIN_POS = -1.f;
    const GLfloat MAX_POS = 1.f;

    GridGraphGenerator grid_graph(NUM_VERTICES_X,
        NUM_VERTICES_Y,
        MIN_POS,
        MAX_POS);

    std::vector<GLfloat> vertices;
    std::vector<GLuint> edges;

    grid_graph.get_graph(vertices, edges);

    const std::size_t DIM = 2;
    const std::size_t NUM_POINTS = NUM_VERTICES_X * NUM_VERTICES_Y * DIM;

    /*for (std::size_t i = 0; i < NUM_POINTS; i += DIM)
    {
        std::cout << "{ " << vertices[i] << "," << vertices[i + 1] << " }" << std::endl;
    }

    std::cout << "# Indices: " << edges.size() << std::endl;

    for (std::size_t i = 0; i < edges.size(); i++)
    {
        std::cout << edges[i] << ", ";
    }*/

    SingleThreadGraphDrawer cpu_drawer(vertices, edges, 5.f, 1.5f, DIM);

    RendererOpenGL renderer_gl(WINDOW_WIDTH,
        WINDOW_HEGHT,
        "Force Directed Graph Drawing",
        VIEWPORT_X,
        VIEWPORT_Y,
        vertices,
        edges,
        cpu_drawer);

    renderer_gl.render();

    return 0;
}