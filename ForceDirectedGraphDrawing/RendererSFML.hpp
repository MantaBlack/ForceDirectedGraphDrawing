#pragma once

#include "IGraphDrawer2D.hpp"
#include "IRenderer.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#include <string>
#include <vector>

class RendererSFML : public IRenderer
{
private:
    IGraphDrawer2D& m_graph_drawer;

    std::size_t m_window_width;
    std::size_t m_window_height;
    std::string m_window_title;
    sf::Font m_render_font;

    std::vector<sf::Vertex> m_edges;
    std::vector<sf::Vertex> m_vertices;

    sf::VertexBuffer m_edges_buffer;
    sf::VertexBuffer m_vertices_buffer;
public:
    RendererSFML(IGraphDrawer2D& graph_drawer,
        std::size_t width,
        std::size_t height,
        std::string title,
        sf::Font font)
        : m_graph_drawer(graph_drawer),
        m_window_width(width),
        m_window_height(height),
        m_window_title(title),
        m_render_font(font)
    {}

    ~RendererSFML()
    {}

    void render() override;
};