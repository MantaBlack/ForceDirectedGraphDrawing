#pragma once

#include "IGraphGenerator.hpp"

class GridGraphGenerator : public IGraphGenerator
{
private:
    const std::size_t DIM = 2;

    std::size_t m_num_vertices_x;
    std::size_t m_num_vertices_y;
    GLfloat m_min_pos;
    GLfloat m_max_pos;

    void generate_vertices(std::vector<GLfloat>& vertices) const;
    void generate_edges(std::vector<GLuint>& edges) const;

public:
    GridGraphGenerator(std::size_t num_vertices_x,
        std::size_t num_vertices_y,
        GLfloat min_pos,
        GLfloat max_pos)
        : m_num_vertices_x(num_vertices_x),
        m_num_vertices_y(num_vertices_y),
        m_min_pos(min_pos),
        m_max_pos(max_pos)
    {}

    ~GridGraphGenerator()
    {}

    void get_graph(std::vector<GLfloat>& vertices, std::vector<GLuint>& edges) override;
};