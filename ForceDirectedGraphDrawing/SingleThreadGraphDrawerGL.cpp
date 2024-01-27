#include "SingleThreadGraphDrawerGL.hpp"

#include <algorithm>

void SingleThreadGraphDrawerGL::calculate_displacements()
{
    std::fill(m_displacements.begin(), m_displacements.end(), 0.f);

    for (std::size_t p = 0; p < m_num_vertices * m_dims; p += m_dims)
    {
        GLfloat my_pos_x = m_vertices[p];
        GLfloat my_pos_y = m_vertices[p + 1];

        for (std::size_t q = p + m_dims; q < m_num_vertices * m_dims; q += m_dims)
        {
            GLfloat diff_x = my_pos_x - m_vertices[q];
            GLfloat diff_y = my_pos_y - m_vertices[q + 1];

            GLfloat dist = sqrt(diff_x * diff_x + diff_y * diff_y);

            GLfloat disp_x = (diff_x / dist) * ((m_spring_const * m_spring_const) / dist);
            GLfloat disp_y = (diff_y / dist) * ((m_spring_const * m_spring_const) / dist);

            m_displacements[q] += disp_x;
            m_displacements[q + 1] += disp_y;
        }
    }
}

void SingleThreadGraphDrawerGL::update_displacements()
{
    // the vector of edges represent pairs of connected vertices
    for (std::size_t i = 0; i < m_edges.size(); i += 2)
    {
        GLfloat vertex_u_x = m_vertices[m_edges[i]];
        GLfloat vertex_u_y = m_vertices[m_edges[i] + 1];

        GLfloat vertex_v_x = m_vertices[m_edges[i + 1]];
        GLfloat vertex_v_y = m_vertices[m_edges[i + 1] + 1];

        GLfloat diff_x = vertex_u_x - vertex_v_x;
        GLfloat diff_y = vertex_u_y - vertex_v_y;

        GLfloat dist = sqrt(diff_x * diff_x + diff_y * diff_y);

        GLfloat disp_x = (diff_x / dist) * ((dist * dist) / m_spring_const);
        GLfloat disp_y = (diff_y / dist) * ((dist * dist) / m_spring_const);

        m_displacements[m_edges[i]] -= disp_x;
        m_displacements[m_edges[i] + 1] -= disp_y;

        m_displacements[m_edges[i + 1]] += disp_x;
        m_displacements[m_edges[i + 1] + 1] += disp_y;
    }
}

void SingleThreadGraphDrawerGL::calculate_vertex_positions()
{
    for (std::size_t p = 0; p < m_num_vertices * m_dims; p += m_dims)
    {
        GLfloat disp_x = m_displacements[p];
        GLfloat disp_y = m_displacements[p + 1];

        GLfloat dist = sqrt(disp_x * disp_x + disp_y * disp_y);

        m_vertices[p] += (disp_x * (m_dampening / dist));
        m_vertices[p + 1] += (disp_y * (m_dampening / dist));
    }
}

void SingleThreadGraphDrawerGL::draw_graph(std::vector<GLfloat>& vertices)
{
    calculate_displacements();
    update_displacements();
    calculate_vertex_positions();

    vertices = std::vector(m_vertices);
}
