#include "GridGraphGenerator.hpp"

#include <random>

static std::random_device g_random_device;
static std::mt19937 g_random_engine(g_random_device());

void GridGraphGenerator::generate_vertices(std::vector<GLfloat>& vertices) const
{
    const std::size_t num_vertices = m_num_vertices_x * m_num_vertices_y;
    vertices.reserve(num_vertices);

    std::uniform_real_distribution<GLfloat> dist(m_min_pos, m_max_pos);

    for (std::size_t i = 0; i < num_vertices; i++)
    {
        for (size_t j = 0; j < DIM; j++)
        {
            vertices.push_back(dist(g_random_engine));
        }
    }
}

void GridGraphGenerator::generate_edges(std::vector<GLuint>& edges) const
{
    GLuint u = 0;
    GLuint v = 1;

    // generate horizontal edges
    // top-down
    for (GLuint i = 0; i < m_num_vertices_y; i++)
    {
        // left-right
        for (GLuint j = 1; j < m_num_vertices_x; j++)
        {
            edges.push_back(u);
            edges.push_back(v);

            ++u;
            ++v;
        }
    }

    // generate vertical edges
    // left-right
    for (GLuint i = 0; i < m_num_vertices_x; i++)
    {
        u = i;
        v = u + m_num_vertices_x;

        // top-down
        for (GLuint j = 1; j < m_num_vertices_y; j++)
        {
            edges.push_back(u);
            edges.push_back(v);

            u += m_num_vertices_x;
            v += m_num_vertices_x;
        }
    }
}

void GridGraphGenerator::get_graph(std::vector<GLfloat>& vertices, std::vector<GLuint>& edges)
{
    generate_edges(edges);
    generate_vertices(vertices);
}