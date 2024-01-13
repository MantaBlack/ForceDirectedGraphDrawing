#pragma once

#include "IGraphDrawer.hpp"

#include <vector>

class SingleThreadGraphDrawer : public IGraphDrawer
{
private:
    std::vector<GLfloat> m_vertices;
    std::vector<GLuint> m_edges;
    GLfloat m_spring_const;
    GLfloat m_dampening;
    std::size_t m_dims;
    std::size_t m_num_vertices;
    std::vector<GLfloat> m_displacements;

    void calculate_displacements();
    void update_displacements();
    void calculate_vertex_positions();

public:
    SingleThreadGraphDrawer(std::vector<GLfloat> vertices,
        std::vector<GLuint> edges,
        GLfloat spring_const,
        GLfloat dampening,
        std::size_t dims)
        : m_vertices(vertices),
        m_edges(edges),
        m_spring_const(spring_const),
        m_dampening(dampening),
        m_dims(dims),
        m_num_vertices(vertices.size() / dims),
        m_displacements(vertices.size())
    {}

    ~SingleThreadGraphDrawer()
    {}

    void draw_graph(std::vector<GLfloat>& vertices) override;
};