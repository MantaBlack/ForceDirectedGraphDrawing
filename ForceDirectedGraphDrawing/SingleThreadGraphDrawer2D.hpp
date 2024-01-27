#pragma once

#include "IGraphDrawer2D.hpp"

#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/Vector2.hpp>

#include <vector>

class SingleThreadGraphDrawer2D : public IGraphDrawer2D
{
private:
    std::vector<sf::Vertex> m_vertices;
    std::vector<sf::Vertex> m_edges;
    float m_spring_const;
    float m_dampening;
    std::vector<sf::Vector2f> m_displacements;

    void calculate_displacements();
    void update_displacements();
    void calculate_vertex_positions();

public:
    SingleThreadGraphDrawer2D(std::vector<sf::Vertex> vertices,
        std::vector<sf::Vertex> edges,
        float spring_const,
        float dampening)
        : m_vertices(vertices),
        m_edges(edges),
        m_spring_const(spring_const),
        m_dampening(dampening),
        m_displacements(vertices.size())
    {}

    ~SingleThreadGraphDrawer2D()
    {}

    void draw_graph(std::vector<sf::Vertex>& vertices) override;
};