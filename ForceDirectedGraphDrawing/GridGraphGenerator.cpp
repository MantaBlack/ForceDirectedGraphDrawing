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

    // top-down
    for (std::size_t i = 0; i < m_num_vertices_y; i++)
    {
        // lef-right
        for (std::size_t j = 1; j < m_num_vertices_x; j++)
        {
            edges.push_back(u);
            edges.push_back(v);

            ++u;
            ++v;
        }

        // when we reach end of row, we jump to next row
        // but we also skip one edge (there is no edge between
        // the last vertex of a row and the first vertex of the
        // next row
        u = u + 2 - 1;
        v = v + 2 - 1;
    }

    // left-right
    for (std::size_t i = 0; i < m_num_vertices_x; i++)
    {
        u = i;
        v = u + m_num_vertices_x;

        // top-down
        for (std::size_t j = 1; j < m_num_vertices_y; j++)
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