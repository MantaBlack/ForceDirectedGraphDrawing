#include "SingleThreadGraphDrawer2D.hpp"

#include <algorithm>

void SingleThreadGraphDrawer2D::calculate_displacements()
{
    std::fill(m_displacements.begin(), m_displacements.end(), sf::Vector2f(0.f, 0.f));

    for (std::size_t p = 0; p < m_vertices.size(); p++)
    {
        sf::Vector2f my_pos = m_vertices[p].position;

        for (std::size_t q = p + 1; q < m_vertices.size(); q++)
        {
            sf::Vector2f diff = my_pos - m_vertices[q].position;
            float distance = sqrt(diff.x * diff.x + diff.y * diff.y);
            sf::Vector2f disp = ((diff / distance) * ((m_spring_const * m_spring_const) / distance));

            m_displacements[p] += disp;

            diff = m_vertices[q].position - my_pos;
            disp = ((diff / distance) * ((m_spring_const * m_spring_const) / distance));
            m_displacements[q] += disp;
        }
    }
}
